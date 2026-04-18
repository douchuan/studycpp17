#include <gtest/gtest.h>

#include "memento_demo.h"

TEST(MementoDemoTest, SaveAndRestore) {
    TextEditor editor("Hello");
    auto m = editor.save();
    editor.set_content("World");
    EXPECT_EQ(editor.content(), "World");
    editor.restore(*m);
    EXPECT_EQ(editor.content(), "Hello");
}

TEST(MementoDemoTest, HistoryStack) {
    TextEditor editor("v1");
    History history;
    history.push(editor.save());
    editor.set_content("v2");
    history.push(editor.save());
    editor.set_content("v3");
    auto m = history.pop();
    editor.restore(*m);
    EXPECT_EQ(editor.content(), "v2");
}
