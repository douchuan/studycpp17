#include <gtest/gtest.h>

#include "adapter_demo.h"

TEST(AdapterDemoTest, AdapterPlaysMp3) {
    Mp3Player player;
    MediaAdapter adapter(&player);
    adapter.play("mp3", "song.mp3");
    EXPECT_EQ(player.played_file(), "song.mp3");
}
