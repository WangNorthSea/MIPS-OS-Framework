#include <os/futex.h>
#include <os/irq.h>
#include <os/mm.h>
#include <assert.h>

futex_bucket_t futex_buckets[FUTEX_BUCKETS];

void init_system_futex()
{
    disable_preempt();
    int i = 0;
    for (i = 0; i < FUTEX_BUCKETS; ++i) {
        init_list_head(&futex_buckets[i]);
    }
    enable_preempt();
}

static int futex_hash(uint32_t x)
{
    unsigned int hash = 0;
	unsigned int y = 0;
    char * str = (char *)&x;
    int i = 0;

	for (i = 0; i < 4; i++) {
		hash = (hash << 4) + *str;
		if ((y = hash & 0xf0000000) != 0) {
			hash ^= (y >> 24);
			hash &= ~y;
		}
		str++;
	}
    hash &= 0x7f;
    
	return hash;
}

static futex_node_t* get_node(volatile uint32_t *val_addr, int create)
{
    int key = futex_hash((uint32_t)val_addr);
    list_node_t *head = &futex_buckets[key];
    list_node_t * p = NULL;
    for (p = head->next; p != head; p = p->next) {
        futex_node_t *node = list_entry(p, futex_node_t, list);
        if (node->futex_key == (uint32_t)val_addr) {
            return node;
        }
    }

    if (create) {
        futex_node_t *node = (futex_node_t*) kmalloc(sizeof(futex_node_t));
        node->futex_key = (uint32_t)val_addr;
        init_list_head(&node->block_queue);
        list_add_tail(&node->list, &futex_buckets[key]);
        return node;
    }

    return NULL;
}

void futex_wait(volatile uint32_t *val_addr, uint32_t val)
{
    disable_preempt();

    futex_node_t *node = get_node(val_addr,1);
    assert(node != NULL);

    if (*val_addr == val) {
        do_block(&current_running->list, &node->block_queue);
        //do_scheduler();
    }

    enable_preempt();
}

void futex_wakeup(volatile uint32_t *val_addr, int num_wakeup)
{
    disable_preempt();
    futex_node_t *node = get_node(val_addr, 0);

    int i = 0;
    if (node != NULL) {
        for (i = 0; i < num_wakeup; ++i) {
            if (list_empty(&node->block_queue)) break;

            do_unblock(node->block_queue.next);
        }
    }

    do_scheduler();
    enable_preempt();
}
