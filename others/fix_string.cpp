#include <iostream>

int main(int argc, char *argv[])
{
  std::string fix_msg;
  std::string to_inject = ",100=";
  auto checksum_tag_pos = fix_msg.rfind(",10=");
  if (checksum_tag_pos != std::string::npos) {
    //auto const checksum_pos = checksum_tag_pos + 4;
    //auto to_inject_checksum = std::accumulate(next(begin(to_inject)), end(to_inject), 1);
    //uint8_t curr_checksum = std::atoi(fix_msg.c_str() + checksum_pos);
    //uint8_t new_checksum = to_inject_checksum + curr_checksum;
    //auto from = std::to_string(new_checksum);
    //std::string to (3, '0');
    //std::copy_backward(begin(from), end(from), end(to));
    //fix_msg.replace(checksum_pos, 3, to);
    fix_msg.insert(checksum_tag_pos, to_inject);
  }

  return 0;
}
