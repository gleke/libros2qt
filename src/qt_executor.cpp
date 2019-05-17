#include "qt_executor.h"

#include "rclcpp/executors/single_threaded_executor.hpp"
#include "rclcpp/any_executable.hpp"
#include "rclcpp/scope_exit.hpp"
#include <thread>

using namespace rclcpp;

QtExecutor::QtExecutor(const rclcpp::executor::ExecutorArgs & args)
: executor::Executor(args) {
    connect(this, &QtExecutor::onNewWork, this, &QtExecutor::processWork, Qt::ConnectionType::BlockingQueuedConnection);
}

QtExecutor::~QtExecutor() {
    m_thread.join();
}

void
QtExecutor::spin()
{
}

void
QtExecutor::start()
{
    m_thread = std::thread([this](){
       while(rclcpp::ok(this->context_))
       {
           wait_for_work();
           printf("Got work !\n");
           onNewWork();
       }
       printf("stopping !\n");
    });
}

void QtExecutor::processWork()
{
    spin_some();
}