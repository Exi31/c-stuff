
#include <stdio.h>
#include <stdlib.h>

// 1. Forward declare and define your struct here
/* YOUR CODE HERE */
typedef struct firewall_session_t {
    int malicious_packets_seen;
    int is_locked_down;
    void (*on_attack_detected)(struct firewall_session_t *self);
} firewall_session_t;

// 2. Implement the state-mutating callback
void lockdown_handler(firewall_session_t *self) {
    if (self->is_locked_down) {
        printf("Firewall is locked down.\n");
        return;
    }

    self->malicious_packets_seen++;

    printf("WARNING MESSAGE: %d malicious packet(s) detected (%d more and the firewall is locked)\n", self->malicious_packets_seen, (3 - self->malicious_packets_seen));

    if (self->malicious_packets_seen == 3) {
        self->is_locked_down = 1;
        printf("Firewall is locked down.\n");
    }
}


int main(void) {
    // 3. Instantiate, initialize, and simulate
    /* YOUR CODE HERE */
    firewall_session_t session1;
    session1.malicious_packets_seen = 0;
    session1.is_locked_down = 0;
    session1.on_attack_detected = lockdown_handler;

    session1.on_attack_detected(&session1);
    session1.on_attack_detected(&session1);
    session1.on_attack_detected(&session1);
    session1.on_attack_detected(&session1);

    return 0;
}