void uncorrupt_memory(std::string &c_mem)
{
    std::regex mul_regex(R"(mul\((\d{1,3}),(\d{1,3})\))");
    std::regex do_regex(R"(do\(\))");
    std::regex dont_regex(R"(don't\(\))");

    std::smatch match;
    int total_sum{0};
    bool mul_enabled = true;

    // Iterate through the memory string
    for (std::sregex_iterator it(c_mem.begin(), c_mem.end(), mul_regex), end; it != end; ++it)
    {
        // Find the last do() and don't() instructions before the current mul instruction
        size_t last_do_pos = std::string::npos;
        size_t last_dont_pos = std::string::npos;

        for (std::sregex_iterator do_it(c_mem.begin(), it->prefix().second, do_regex); do_it != std::sregex_iterator(); ++do_it)
        {
            last_do_pos = do_it->position();
        }

        for (std::sregex_iterator dont_it(c_mem.begin(), it->prefix().second, dont_regex); dont_it != std::sregex_iterator(); ++dont_it)
        {
            last_dont_pos = dont_it->position();
        }

        // Determine mul instruction enablement based on the most recent instruction
        if (last_do_pos != std::string::npos &&
            (last_dont_pos == std::string::npos || last_do_pos > last_dont_pos))
        {
            mul_enabled = true;
        }
        else if (last_dont_pos != std::string::npos &&
                 (last_do_pos == std::string::npos || last_dont_pos > last_do_pos))
        {
            mul_enabled = false;
        }

        // Process mul instruction if enabled
        if (mul_enabled)
        {
            int x = std::stoi((*it)[1]);
            int y = std::stoi((*it)[2]);

            total_sum += x * y;
            std::cout << "Found enabled: mul(" << x << "," << y << ") => " << x * y << std::endl;
        }
    }

    std::cout << "Total sum of enabled mul instructions: " << total_sum << std::endl;
}


void uncorrupt_memory(std::string &c_mem)
{
    std::regex mul_regex(R"(mul\((\d{1,3}),(\d{1,3})\))");
    std::smatch match;
    int total_sum{0};
    bool mul_enabled = true;


    auto begin = std::sregex_iterator(c_mem.begin(), c_mem.end(), mul_regex);
    auto end = std::sregex_iterator();

    for (auto it = begin; it != end; ++it)
    {
        int x = std::stoi((*it)[1]); 
        int y = std::stoi((*it)[2]);
        
        total_sum += x * y;

        std::cout << "Found: mul(" << x << "," << y << ") => " << x * y << std::endl;
    }

    std::cout << "Total sum of valid mul instructions: " << total_sum << std::endl;
}