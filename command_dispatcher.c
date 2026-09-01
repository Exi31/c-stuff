
#include <stdio.h>

typedef struct device_state_t {
    const char *device_name;
    int value;
} device_state_t;

typedef void (*action_fn)(device_state_t *state, int arg);

typedef struct command_t {
    const char *cmd_name;
    action_fn handler;
} command_t;

void add_action(device_state_t *state, int arg) {
    state->value += arg;
    printf("New value of %s: %d\n", state->device_name, state->value);
}

void set_action(device_state_t *state, int arg) {
    state->value = arg;
    printf("New value of %s: %d\n", state->device_name, state->value);
}

int main(void) {
    command_t table[2] = {
        {"ADD", add_action},
        {"SET", set_action}
    };

    device_state_t device1 = {"Sensor_A", 0};

    table[0].handler(&device1, 15);
    table[0].handler(&device1, 5);
    table[1].handler(&device1, 100);

    return 0;
}