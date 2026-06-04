#include <gtest/gtest.h>
#include <filesystem>
#include <string>
#include <iostream>
#include <fstream>

#include "core/Repository.h"
#include "commands/ICommand.h"
#include "commands/AddCommand.h"

TEST(RepositoryTest, InitCreatesRepository){

    std::filesystem::remove_all(".mygit");

    Repository repo;

    EXPECT_TRUE(repo.init());

    EXPECT_TRUE(std::filesystem::exists(".mygit"));
    
    EXPECT_TRUE(std::filesystem::exists(".mygit/commits"));
    
    EXPECT_TRUE(std::filesystem::exists(".mygit/staging"));
    
    EXPECT_TRUE(std::filesystem::exists(".mygit/HEAD"));

    std::ifstream head(".mygit/HEAD");

    std::string value;

    std::getline(head, value);

    EXPECT_EQ(value, "0");

    std::filesystem::remove_all(".mygit");
}

TEST(RepositoryTest, AddCommit){

    std::filesystem::remove_all(".mygit");

    Repository repo;

    repo.init();

    std::unique_ptr<ICommand> cmd = std::make_unique<AddCommand>();

    std::ofstream file("hello.txt");

    file << "hello world";

    file.close();

    std::vector<std::string> args = {"hello.txt"};

    cmd->execute(args);

    EXPECT_TRUE(std::filesystem::exists(".mygit/staging/hello.txt"));

    std::ifstream staged(".mygit/staging/hello.txt");

    std::string contest;

    std::getline(staged, contest);

    EXPECT_EQ(contest, "hello world");

    std::filesystem::remove("hello.txt");

    std::filesystem::remove_all(".mygit");
}