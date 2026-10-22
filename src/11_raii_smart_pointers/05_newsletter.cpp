// === Lesson: Choosing who owns what ==========================================
//
// Every heap object in C++ needs an answer to "who deletes this?". The type you
// hold it by is that answer, and it's the first design decision for a class:
//
//     std::unique_ptr<T>   I'm the only owner           (a node owns its child)
//     std::shared_ptr<T>   I'm one of several owners    (a tree's nodes)
//     std::weak_ptr<T>     I want it if it still exists (a cache, a listener list)
//     T& or T*             I'm borrowing it, and it surely outlives me
//                          (a function parameter, a view into a container)
//
// Start with unique_ptr (or a plain member) and reach for shared_ptr only when
// ownership really is shared. A raw pointer or reference that outlives its
// object dangles, and nothing stops you from using it: that's undefined behavior.
//
// weak_ptr is the tool for "observers": objects that get told about events but
// shouldn't decide how long anyone lives. Each time you need one, lock() it and
// skip it if it's gone. A cache works the same way:
//
//     std::map<std::string, std::weak_ptr<Image>> cache;
//
//     std::shared_ptr<Image> load(const std::string &path) {
//         if (auto cached = cache[path].lock()) return cached;  // still in use
//         auto image = std::make_shared<Image>(read_image(path));
//         cache[path] = image;     // remember it without keeping it alive
//         return image;
//     }
//
// Once every caller drops its shared_ptr, the Image is freed and its entry
// expires. A list of weak_ptrs collects expired entries like that over time, so
// prune them now and then, or they pile up.
//
// weak_ptr has no ==. To check whether one refers to a particular object, lock()
// it and compare the result with that object's shared_ptr.
//
// Read more: https://www.learncpp.com/cpp-tutorial/circular-dependency-issues-with-stdshared_ptr-and-stdweak_ptr/
//
// === Challenge: Newsletter ===================================================
// A Newsletter delivers messages to its subscribers but doesn't own them: when
// a subscriber is destroyed elsewhere, the newsletter simply stops delivering
// to it. Store std::weak_ptr<Subscriber> and lock() each one when you need it.
//
// ./grade 11_raii_smart_pointers/05_newsletter

#include <algorithm>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Subscriber {
public:
    explicit Subscriber(std::string name) : name_(std::move(name)) {}

    const std::string &name() const { return name_; }
    const std::vector<std::string> &inbox() const { return inbox_; }
    void receive(const std::string &message) { inbox_.push_back(message); }

private:
    std::string name_;
    std::vector<std::string> inbox_;
};

class Newsletter {
public:
    // Start delivering to subscriber.
    // Subscribing someone twice changes nothing: they still get each message once.
    //
    // Example:
    //   auto ada = std::make_shared<Subscriber>("Ada");
    //   news.subscribe(ada);
    //   news.subscribe(ada);   // no change: news.subscriber_count() is still 1
    //
    // The newsletter doesn't own ada: once her last shared_ptr is gone, she's destroyed.
    void subscribe(const std::shared_ptr<Subscriber> &subscriber) {
        throw "TODO";
    }

    // Stop delivering to subscriber, and return true.
    // Return false if they weren't subscribed.
    //
    // Example:
    //   news has subscribers ada and bob
    //   news.unsubscribe(ada) == true    // publish now reaches only bob
    //   news.unsubscribe(ada) == false   // ada isn't subscribed any more
    bool unsubscribe(const std::shared_ptr<Subscriber> &subscriber) {
        throw "TODO";
    }

    // Deliver message to every live subscriber, in the order they subscribed.
    // Forget subscribers that no longer exist.
    // Return how many subscribers received it.
    //
    // Example:
    //   news has subscribers ada and bob
    //   news.publish("hello") == 2   // both inboxes now hold "hello"
    //   ada.reset();                 // her last owner lets go: Ada is destroyed
    //   news.publish("news") == 1    // only Bob receives it
    //
    // lock() each weak_ptr; a null result means that subscriber is gone.
    int publish(const std::string &message) {
        throw "TODO";
    }

    // Return how many subscribers are still alive.
    //
    // Example:
    //   news has subscribers ada and bob, so news.subscriber_count() == 2
    //   bob.reset();   // Bob is destroyed
    //   news.subscriber_count() == 1
    int subscriber_count() const {
        throw "TODO";
    }

    // Return the names of the live subscribers, in the order they subscribed.
    //
    // Example:
    //   news has subscribers ada, bob and cy, in that order
    //   bob.reset();   // Bob is destroyed
    //   news.subscriber_names() == {"Ada", "Cy"}
    std::vector<std::string> subscriber_names() const {
        throw "TODO";
    }

private:
    // TODO: the data members you need
};
