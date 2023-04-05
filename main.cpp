#include <sys/mman.h>

#include <array>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <gsl/gsl>
#include <iomanip>
#include <iostream>
#include <memory>
#include <span>
#include <vector>

static const int LENGTH = 8;

auto main(int argc, char *argv[]) -> int {
  std::vector<std::string> args(argv, argv + argc);
  std::array<char, 256> err_buf = {0};
  std::unique_ptr<std::FILE, std::function<void(std::FILE *)>> file(
      std::fopen(args[1].c_str(), "r"),
      [&err_buf](gsl::owner<std::FILE *> file) {
        if (std::fclose(file) != 0) {
          strerror_r(errno, err_buf.data(), sizeof(err_buf));
          std::cerr << "Close File Failed: " << err_buf.data() << std::endl;
        }
      });

  if (!file) {
    strerror_r(errno, err_buf.data(), sizeof(err_buf));
    std::cerr << "Open File Failed: " << err_buf.data() << std::endl;
    return EXIT_FAILURE;
  }

  if (std::fseek(file.get(), 0, SEEK_END) == -1) {
    strerror_r(errno, err_buf.data(), sizeof(err_buf));
    std::cerr << "Seek File Failed: " << err_buf.data() << std::endl;
    return EXIT_FAILURE;
  }

  auto size = std::ftell(file.get());
  if (size == -1) {
    strerror_r(errno, err_buf.data(), sizeof(err_buf));
    std::cerr << "Tell File Failed: " << err_buf.data() << std::endl;
    return EXIT_FAILURE;
  }

  int file_no = fileno(file.get());
  void *addr = mmap(nullptr, size, PROT_READ, MAP_SHARED, file_no, 0);
  if (addr == MAP_FAILED) {
    strerror_r(errno, err_buf.data(), sizeof(err_buf));
    std::cerr << "Failed to mmap file:" << err_buf.data() << std::endl;
    return EXIT_FAILURE;
  }

  std::unique_ptr<void, std::function<void(void *)>> content(
      addr, [size](void *addr) { munmap(addr, static_cast<size_t>(size)); });

  std::span<unsigned char> arr(static_cast<unsigned char *>(content.get()),
                               size);
  for (int i = 0; i < LENGTH; ++i) {
    std::cout << std::uppercase << std::hex << std::setfill('0') << std::setw(2)
              << static_cast<unsigned int>(arr[i]) << std::endl;
  }
  return 0;
}
