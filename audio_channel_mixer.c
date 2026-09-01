
#include <stdio.h>

typedef struct audio_channel_t {
    const char *channel_name;
    int volume;     // valid range 0-100
    int is_muted;    // 0 = unmuted, 1 = muted
} audio_channel_t;

typedef void (*audio_op_fn)(audio_channel_t *, int);

void volume_up(audio_channel_t *self, int delta) {
    self->volume += delta;
    self->volume = (self->volume > 100) ? 100 : self->volume;
    printf("%s's new volume: %d\n", self->channel_name, self->volume);
}

void volume_down(audio_channel_t *self, int delta) {
    self->volume -= delta;
    self->volume = (self->volume < 0) ? 0 : self->volume;
    printf("%s's new volume: %d\n", self->channel_name, self->volume);
}

void toggle_mute(audio_channel_t *self, int delta) {
    self->is_muted = delta;
    printf("%s is %s\n", self->channel_name, (self->is_muted ? "MUTED" : "UNMUTED"));
}

typedef struct audio_cmd_t {
    const char *name;   // VOL_UP/VOL_DOWN/MUTE
    audio_op_fn handler;
} audio_cmd_t;

int main(void) {
    audio_channel_t channel1 = {"Master", 50, 0};

    audio_cmd_t table[3] = {
        {"VOL_UP", volume_up},
        {"VOL_DOWN", volume_down},
        {"MUTE", toggle_mute}
    };

    table[0].handler(&channel1, 30);
    table[0].handler(&channel1, 40);
    table[1].handler(&channel1, 60);
    table[2].handler(&channel1, 1);

    return 0;
}

