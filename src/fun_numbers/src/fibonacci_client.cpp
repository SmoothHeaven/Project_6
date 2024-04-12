
#include "number_actions/action/fibonacci.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"

using Fibonacci = number_actions::action::Fibonacci;

class FibonacciClient : public rclcpp::Node {
public:
    explicit FibonacciClient(const std::string& action_name)
        : Node("fibonacci_client"), action_name_(action_name) {
        client_ = rclcpp_action::create_client<Fibonacci>(
            this,
            action_name_);
        RCLCPP_INFO(this->get_logger(), "Client is started.");
    }

    bool send_goal(int order) {
        if (!client_->wait_for_action_server(std::chrono::seconds(10))) {
            RCLCPP_ERROR(this->get_logger(), "Action server not available after waiting");
            return false;
        }

        auto goal_msg = Fibonacci::Goal();
        goal_msg.order = order;

        auto send_goal_options = rclcpp_action::Client<Fibonacci>::SendGoalOptions();
        send_goal_options.goal_response_callback =
            [this](auto) { RCLCPP_INFO(this->get_logger(), "Goal accepted by server"); };


        send_goal_options.feedback_callback =
            [this](auto, const auto& feedback) {
                if (!feedback->partial_sequence.empty()) {
                    RCLCPP_INFO(this->get_logger(), "Next number in sequence received: %d", feedback->partial_sequence.back());
                }
            };

        send_goal_options.result_callback =
            [this](const auto& result) {
                if (result.code == rclcpp_action::ResultCode::SUCCEEDED) {
                    std::stringstream ss;
                    ss << "Result received: ";
                    for (auto number : result.result->sequence) {
                        ss << number << ", ";
                    }
                    RCLCPP_INFO(this->get_logger(), "%s", ss.str().c_str());
                } else {
                    RCLCPP_ERROR(this->get_logger(), "Goal failed");
                }
                rclcpp::shutdown();
            };

        RCLCPP_INFO(this->get_logger(), "Client is sending the goal...");
        client_->async_send_goal(goal_msg, send_goal_options);
        return true;
    }

private:
    std::string action_name_;
    rclcpp_action::Client<Fibonacci>::SharedPtr client_;
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);

    auto fibonacci_client = std::make_shared<FibonacciClient>("fibonacci");
    if (fibonacci_client->send_goal(10)) { // Sends a goal with the order of 10
        rclcpp::spin(fibonacci_client);
    }

    rclcpp::shutdown();
    return 0;
}
