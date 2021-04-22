#include <boost/program_options.hpp>
#include <dbWrapper.hpp>

#include "iostream"
namespace po = boost::program_options;

int main(int argc, char* argv[]) {
  po::options_description desc(
      "Usage:\n  dbcs [options] <path/to/input/storage.db>\nMust have options");
  desc.add_options()("help", "produce help message")(
      "log-level", po::value<std::string>(),
      "info|warning|error \ndefault: error")("thread-count", po::value<int>(),
                                             "default: count of logical "
                                             "core")("output ",
                                                     po::value<std::string>(),
                                                     "<path/to/output/"
                                                     "storage.db>\ndefault:"
                                                     " <path/to/input/"
                                                     "dbcs-storage.db>");

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  rocksdbWrapper db = rocksdbWrapper(10, "/home/rinat/labs/databasa");
  db.loadNewDB();
  std::map<std::string, std::string> kvStorage;
  db.getValues(kvStorage);
  /*for (std::map<std::string,std::string>::iterator it=kvStorage.begin(); it!=kvStorage.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';*/


  if (vm.count("help")) {
    std::cout << desc << "\n";
    return 1;
  }
}