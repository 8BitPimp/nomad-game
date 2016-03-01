#pragma once
#include <stdint.h>
#include <assert.h>

struct point_t {
    point_t() {}

    point_t(int32_t a, int32_t b) : x(a), y(b) {}

    int32_t x, y;
};

// handles all window drawing operations
struct window_draw_t {
    uint32_t *pixels_;
    int32_t width_;
    int32_t height_;

    void circle(const point_t &pos, int32_t radius, uint32_t rgb);

    void plot(const point_t &p, uint32_t rgb);

    void fill(uint32_t rgb);
};

// handles all game window operations
struct window_t {
    window_draw_t draw_;

    static window_t &inst() {
        static window_t *wnd = new window_t;
        assert(wnd);
        return *wnd;
    }

    static window_draw_t &draw() { return inst().draw_; }

    bool init(uint32_t width, uint32_t height);
    void free();

    bool tick();

  private:
    struct detail_t;
    detail_t *detail_;

    window_t();
};