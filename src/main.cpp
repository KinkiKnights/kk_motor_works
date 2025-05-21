#include "rclcpp/rclcpp.hpp"
#include "kk_driver_msg/msg/motor_cmd.hpp"


class motor_works_node : public rclcpp::Node{
public:
    rclcpp::Publisher<kk_driver_msg::msg::MotorCmd>::SharedPtr motor_cmd_pub;
    kk_driver_msg::msg::MotorCmd motor1_cmd_msg;
    kk_driver_msg::msg::MotorCmd motor2_cmd_msg;
    rclcpp::TimerBase::SharedPtr timer_;

    float duty[4] = {1.f, 1.f, 1.f, 1.f};

    void update(){

        motor1_cmd_msg.child_id = 0;
        motor1_cmd_msg.port.resize(2);
        motor1_cmd_msg.ctrl.resize(2);
        motor1_cmd_msg.target.resize(2);

        motor2_cmd_msg.child_id = 1;
        motor2_cmd_msg.port.resize(2);
        motor2_cmd_msg.ctrl.resize(2);
        motor2_cmd_msg.target.resize(2);
        
        motor1_cmd_msg.port[0] = 0;
        motor1_cmd_msg.ctrl[0] = 1;
        motor1_cmd_msg.target[0] = static_cast<int32_t>(duty[0] * 0xFFFFF);

        motor1_cmd_msg.port[1] = 1;
        motor1_cmd_msg.ctrl[1] = 1;
        motor1_cmd_msg.target[1] = static_cast<int32_t>(duty[1] * 0xFFFFF);

        motor2_cmd_msg.port[0] = 0;
        motor2_cmd_msg.ctrl[0] = 1;
        motor2_cmd_msg.target[0] = static_cast<int32_t>(duty[2] * 0xFFFFF);

        motor2_cmd_msg.port[1] = 1;
        motor2_cmd_msg.ctrl[1] = 1;
        motor2_cmd_msg.target[1] = static_cast<int32_t>(duty[3] * 0xFFFFF);
        
        motor_cmd_pub->publish(motor1_cmd_msg);
        motor_cmd_pub->publish(motor2_cmd_msg);
    }

    motor_works_node() : Node("motor_works_node_node"){
        motor_cmd_pub = this->create_publisher<kk_driver_msg::msg::MotorCmd>("mtr/cmd", rclcpp::QoS(10));
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(50), // 1秒ごとに実行
            std::bind(&motor_works_node::update, this));    
    }

};



int main(int argc, char *argv[]) {
    // ROS 2クライアントライブラリの初期化
    rclcpp::init(argc, argv);
    // ノードの作成と実行
    auto node = std::make_shared<motor_works_node>();
    // スピン処理
    rclcpp::spin(node);
    // ROS 2クライアントライブラリの終了処理
    rclcpp::shutdown();
    return 0;
}