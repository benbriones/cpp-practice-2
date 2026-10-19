// Challenge: Newsletter
// A Newsletter delivers messages to its subscribers but doesn't own them: when
// a subscriber is destroyed elsewhere, the newsletter simply stops delivering
// to it. Store std::weak_ptr<Subscriber> and lock() each one when you need it.
//
// Two weak_ptrs (or a weak_ptr and a shared_ptr) refer to the same object when
// w.lock() == s.
//
// Grade: grade 11_raii_smart_pointers/05_newsletter

#include <algorithm>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Subscriber {
public:
    explicit Subscriber(std::string name) : name_(std::move(name)) {}

    const std::string& name() const { return name_; }
    const std::vector<std::string>& inbox() const { return inbox_; }
    void receive(const std::string& message) { inbox_.push_back(message); }

private:
    std::string name_;
    std::vector<std::string> inbox_;
};

class Newsletter {
public:
    // Start delivering to subscriber. Subscribing someone twice changes nothing.
    void subscribe(const std::shared_ptr<Subscriber>& subscriber) {
        throw "TODO";
    }

    // Stop delivering to subscriber. Return false if they weren't subscribed.
    bool unsubscribe(const std::shared_ptr<Subscriber>& subscriber) {
        throw "TODO";
    }

    // Deliver message to every live subscriber, in the order they subscribed,
    // and forget subscribers that no longer exist. Return how many received it.
    int publish(const std::string& message) {
        throw "TODO";
    }

    // How many subscribers are still alive.
    int subscriber_count() const {
        throw "TODO";
    }

    // Names of the live subscribers, in the order they subscribed.
    std::vector<std::string> subscriber_names() const {
        throw "TODO";
    }

private:
    // TODO: the data members you need
};
