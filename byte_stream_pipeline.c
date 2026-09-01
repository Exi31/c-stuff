
#include <stdio.h>

typedef struct stream_ctx_t {
    const char *stream_name;
    int transforms_applied;
    int bytes_modified;
} stream_ctx_t;

typedef void (*filter_fn)(stream_ctx_t *, char *, int);

void filter_strip_vowels(stream_ctx_t *self, char *buffer, int len) {
    for (int i = 0; i < len; i++) {
        if (buffer[i] == 'a' || buffer[i] == 'e' || buffer[i] == 'i' || buffer[i] == 'o' || buffer[i] == 'u') {
            buffer[i] = '_';
            self->bytes_modified++;
        }
    }

    self->transforms_applied++;
}

void filter_leetspeak(stream_ctx_t *self, char *buffer, int len) {
    for (int i = 0; i < len; i++) {
        if (buffer[i] == 'e' || buffer[i] == 'E') {
            buffer[i] = '3';
            self->bytes_modified++;
        }

        else if (buffer[i] == 'l' || buffer[i] == 'L') {
            buffer[i] = '1';
            self->bytes_modified++;
        }

        else if (buffer[i] == 't' || buffer[i] == 'T') {
            buffer[i] = '7';
            self->bytes_modified++;
        }
    }

    self->transforms_applied++;
}

void filter_reverse(stream_ctx_t *self, char *buffer, int len) {
    for (int i = 0; i < len / 2; i++) {
        char temp = buffer[i];
        buffer[i] = buffer[len - 1 - i];
        buffer[len - 1 - i] = temp;
    }

    self->transforms_applied++;
}

int main(void) {
    stream_ctx_t context = {"Ingress_Eth0", 0, 0};

    char payload[] = "elite hacker network";

    filter_fn pipeline[3] = {filter_strip_vowels, filter_leetspeak, filter_reverse};

    for (int i = 0; i < 3; i++) {
        pipeline[i](&context, payload, sizeof(payload) - 1);
    }

    printf("Final string: %s\nTransform(s) applied: %d\nByte(s) modified: %d\n", payload, context.transforms_applied, context.bytes_modified);

    return 0;
}

