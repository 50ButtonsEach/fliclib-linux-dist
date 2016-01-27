#include <iostream>

#include "flic.hpp"

class ButtonEventListener : public flic::client::button::ButtonEventListener {
public:
    virtual std::string getHash() override {
	return "main";
    }

    virtual void onButtonUpOrDown(const std::string& deviceId,
				  const bool& queued,
				  const int& timeDiff,
				  const bool& isUp,
				  const bool& isDown) override {
	std::cout << deviceId << (isUp ? " up" : " down") << std::endl;
    }
};

class ButtonListener : public flic::client::manager::ButtonListener {
private:
    std::shared_ptr<flic::client::manager::Manager> manager;
public:
    ButtonListener(std::shared_ptr<flic::client::manager::Manager> manager) :
	manager(manager) {

    }

    virtual std::string getHash() override {
	return "main";
    }

    virtual void onButtonDiscover(const std::string& deviceId) override {
	auto button = manager->getButton(deviceId);
	button->addButtonEventListener(std::shared_ptr<flic::client::button::ButtonEventListener>(new ButtonEventListener()));
    }
};

int main() {
    flic::client::Client client;

    try {
	client.start([&client] () {
	        std::cout << "Initialized" << std::endl;
		auto manager = client.getManager();

		for (auto& button : manager->getButtons()) {
		    button->addButtonEventListener(std::shared_ptr<flic::client::button::ButtonEventListener>(new ButtonEventListener()));
		}
	    }, [&client] (const bool& resumable) {
	        std::cout << "Uninitialized" << std::endl;
	    });
	client.run();
    } catch (flic::client::ClientNetworkException& e) {
	std::cerr << e.what() << std::endl;
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown exception" << std::endl;
    }
}
