#ifndef LINDAPP_LOGGER_HPP_INCLUDED__
#define LINDAPP_LOGGER_HPP_INCLUDED__

#include <string>
#include <cstddef>
#include <fstream>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace gfj{

template <class Func>
class logger{
    Func gen;
    std::size_t count;
    std::string const file;
public:

    logger(Func const& gen, std::string const& name = "log.txt")
        : gen(gen), count(0), file(name)
    {
        reset_file();
    }

    template<class... Args>
    void record(Args &&... args)
    {
        using namespace boost::posix_time;
        auto text = gen(std::forward<Args>(args)...);

        std::ofstream ofs(file, std::ios_base::out | std::ios_base::app);
        ofs << "\n*** beginning of log " << count << " *** at "
               << boost::posix_time::to_iso_extended_string( second_clock::universal_time() ) << "\n"
               << text << "\n*** end of log " << count << " ***\n" << std::flush;
        ofs.close();

        count++;
    }

    void reset_file()
    {
        std::ofstream ofs(file);
        ofs.close();
    }

    void new_log_generator(Func const& new_gen)
    {
        gen = new_gen;
    }

    virtual ~logger(){}
};

template <class Func>
logger<Func> make_logger(Func const& f, std::string const& name = "log.txt")
{
    return std::move(logger<Func>(f, name));
}

}
#endif // LINDAPP_LOGGER_HPP_INCLUDED__
