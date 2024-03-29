struct test_display
{
    struct area area;
    CGPoint area_max;
};

static inline void init_test_display_list(struct test_display display_list[3])
{
    display_list[0].area.x     = 0;
    display_list[0].area.y     = 0;
    display_list[0].area.w     = 2560;
    display_list[0].area.h     = 1440;
    display_list[0].area_max.x = display_list[0].area.x + display_list[0].area.w - 1;
    display_list[0].area_max.y = display_list[0].area.y + display_list[0].area.h - 1;

    display_list[1].area.x     = -1728;
    display_list[1].area.y     = 0;
    display_list[1].area.w     = 1728;
    display_list[1].area.h     = 1117;
    display_list[1].area_max.x = display_list[1].area.x + display_list[1].area.w - 1;
    display_list[1].area_max.y = display_list[1].area.y + display_list[1].area.h - 1;

    display_list[2].area.x     = 2560;
    display_list[2].area.y     = 0;
    display_list[2].area.w     = 1920;
    display_list[2].area.h     = 1080;
    display_list[2].area_max.x = display_list[2].area.x + display_list[2].area.w - 1;
    display_list[2].area_max.y = display_list[2].area.y + display_list[2].area.h - 1;
}

TEST_FUNC(display_area_is_in_direction,
{
    struct test_display display_list[3];
    init_test_display_list(display_list);

    bool t1 = area_is_in_direction(&display_list[0].area, display_list[0].area_max, &display_list[1].area, display_list[1].area_max, DIR_WEST);
    TEST_CHECK(t1, true);

    bool t2 = area_is_in_direction(&display_list[0].area, display_list[0].area_max, &display_list[2].area, display_list[2].area_max, DIR_WEST);
    TEST_CHECK(t2, false);
});

static inline int test_display_in_direction(struct test_display *display_list, int display_count, int source, int direction)
{
    int best_index    = -1;
    int best_distance = INT_MAX;

    for (int i = 0; i < display_count; ++i) {
        if (i == source) continue;

        bool direction = area_is_in_direction(&display_list[source].area, display_list[source].area_max, &display_list[i].area, display_list[i].area_max, DIR_WEST);
        if (direction) {
            int distance = area_distance_in_direction(&display_list[source].area, display_list[source].area_max, &display_list[i].area, display_list[i].area_max, DIR_WEST);
            if (distance < best_distance) {
                best_index = i;
                best_distance = distance;
            }
        }
    }

    return best_index;
}

TEST_FUNC(display_area_distance_in_direction,
{
    int best_index;
    struct test_display display_list[3];
    init_test_display_list(display_list);

    best_index = test_display_in_direction(display_list, array_count(display_list), 0, DIR_WEST);
    TEST_CHECK(best_index, 1);

    best_index = test_display_in_direction(display_list, array_count(display_list), 1, DIR_WEST);
    TEST_CHECK(best_index, -1);

    best_index = test_display_in_direction(display_list, array_count(display_list), 2, DIR_WEST);
    TEST_CHECK(best_index, 0);
});
