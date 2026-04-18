#include <gtest/gtest.h>

#include "builder_demo.h"

TEST(BuilderDemoTest, FluentBuild) {
    HttpRequest req =
        HttpRequestBuilder().method("GET").url("http://example.com").body("hello").build();
    EXPECT_EQ(req.build(), "GET http://example.com\nhello");
}

TEST(BuilderDemoTest, EmptyBody) {
    HttpRequest req = HttpRequestBuilder().method("POST").url("/api").build();
    EXPECT_EQ(req.build(), "POST /api\n");
}
