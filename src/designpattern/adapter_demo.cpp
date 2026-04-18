#include "adapter_demo.h"

#include <iostream>

int main() {
    Mp3Player mp3;
    MediaAdapter adapter(&mp3);
    adapter.play("mp3", "song.mp3");
    std::cout << "played: " << mp3.played_file() << "\n";
    return 0;
}
