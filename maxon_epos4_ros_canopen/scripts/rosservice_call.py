import subprocess
import time

def call_service():
    command = ['rosservice', 'call', '/maxon/driver/get_object', 'base_link1_joint', '30D1sub02', 'false']
    result = subprocess.check_output(command)
    return result.decode('utf-8')

if __name__ == '__main__':
    # 定义保存结果的文件路径
    output_file = '/home/ubuntu/service_results.txt'

    while True:
        try:
            # 调用服务并获取结果
            result = call_service()

            # 保存结果到文件
            with open(output_file, 'a') as f:
                f.write(result)

            # 等待1秒
            time.sleep(1.0)

        except subprocess.CalledProcessError as e:
            print(f"Service call failed: {str(e)}")
            break
