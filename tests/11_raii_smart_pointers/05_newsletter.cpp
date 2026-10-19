#include "grader.hpp"
#include "11_raii_smart_pointers/05_newsletter.cpp"

TEST("publish: delivers to every subscriber") {
    Newsletter news;
    auto ada = std::make_shared<Subscriber>("Ada");
    auto bob = std::make_shared<Subscriber>("Bob");
    news.subscribe(ada);
    news.subscribe(bob);
    CHECK_EQ(news.publish("hello"), 2);
    news.publish("again");
    CHECK_EQ(ada->inbox(), {"hello", "again"});
    CHECK_EQ(bob->inbox(), {"hello", "again"});
}

TEST("publish: with no subscribers") {
    Newsletter news;
    CHECK_EQ(news.publish("anyone?"), 0);
}

TEST("subscribe: the newsletter doesn't keep subscribers alive") {
    Newsletter news;
    auto ada = std::make_shared<Subscriber>("Ada");
    std::weak_ptr<Subscriber> watch = ada;
    news.subscribe(ada);
    ada.reset();
    CHECK(watch.expired(), "Ada should be destroyed once the last shared_ptr to her is gone");
}

TEST("publish: skips subscribers that were destroyed") {
    Newsletter news;
    auto ada = std::make_shared<Subscriber>("Ada");
    auto bob = std::make_shared<Subscriber>("Bob");
    news.subscribe(ada);
    news.subscribe(bob);
    ada.reset();
    CHECK_EQ(news.publish("news"), 1);
    CHECK_EQ(bob->inbox(), {"news"});
}

TEST("subscriber_count: only live subscribers") {
    Newsletter news;
    auto ada = std::make_shared<Subscriber>("Ada");
    auto bob = std::make_shared<Subscriber>("Bob");
    news.subscribe(ada);
    news.subscribe(bob);
    CHECK_EQ(news.subscriber_count(), 2);
    bob.reset();
    CHECK_EQ(news.subscriber_count(), 1);
}

TEST("subscribe: twice is the same as once") {
    Newsletter news;
    auto ada = std::make_shared<Subscriber>("Ada");
    news.subscribe(ada);
    news.subscribe(ada);
    CHECK_EQ(news.subscriber_count(), 1);
    news.publish("once");
    CHECK_EQ(ada->inbox(), {"once"});
}

TEST("unsubscribe") {
    Newsletter news;
    auto ada = std::make_shared<Subscriber>("Ada");
    auto bob = std::make_shared<Subscriber>("Bob");
    news.subscribe(ada);
    news.subscribe(bob);
    CHECK_EQ(news.unsubscribe(ada), true);
    news.publish("only bob");
    CHECK_EQ(ada->inbox(), {});
    CHECK_EQ(bob->inbox(), {"only bob"});
    CHECK_EQ(news.unsubscribe(ada), false);
}

TEST("subscriber_names: live subscribers in order") {
    Newsletter news;
    auto ada = std::make_shared<Subscriber>("Ada");
    auto bob = std::make_shared<Subscriber>("Bob");
    auto cy = std::make_shared<Subscriber>("Cy");
    news.subscribe(ada);
    news.subscribe(bob);
    news.subscribe(cy);
    bob.reset();
    CHECK_EQ(news.subscriber_names(), {"Ada", "Cy"});
}

TEST("one subscriber, several newsletters") {
    Newsletter tech;
    Newsletter sport;
    auto ada = std::make_shared<Subscriber>("Ada");
    tech.subscribe(ada);
    sport.subscribe(ada);
    tech.publish("C++26 news");
    sport.publish("match report");
    CHECK_EQ(ada->inbox(), {"C++26 news", "match report"});
}
