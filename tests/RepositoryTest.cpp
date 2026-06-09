#include <gtest/gtest.h>
#include <filesystem>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "core/Repository.h"
#include "core/CommitManager.h"
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

TEST(RepositoryTest, AddCommands){

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

    std::string content;

    std::getline(staged, content);

    EXPECT_EQ(content, "hello world");

    std::filesystem::remove_all(".mygit");
}

TEST(RepositoryTest, ReadHead){

    std::filesystem::remove_all(".mygit");

    Repository repo;

    repo.init();

    std::string content = repo.readHead();

    EXPECT_EQ(content, "0");

    std::filesystem::remove_all(".mygit");
}

TEST(RepositoryTest, updateHead){

    std::filesystem::remove_all(".mygit");

    Repository repo;

    repo.init();

    repo.updateHead("3");

    std::string content = repo.readHead();

    EXPECT_EQ(content, "3");

    std::filesystem::remove_all(".mygit");
}

TEST(RepositoryTest, getCommitsPath){

    std::filesystem::remove_all(".mygit");

    Repository repo;

    repo.init();

    std::filesystem::path commitpath = repo.getCommitsPath();

    std::filesystem::path realpath(".mygit/commits");
    
    EXPECT_EQ(commitpath, realpath);

    std::filesystem::remove_all(".mygit");
}

TEST(CommitManagerTest, createCommit){
    std::filesystem::remove_all(".mygit");

    Repository repo;

    CommitManager commitManager(repo);

    std::string message = "message";

    EXPECT_EQ(commitManager.createCommit(message), false);
    
    repo.init();

    EXPECT_EQ(commitManager.createCommit(message), false);

    std::unique_ptr<ICommand> cmd = std::make_unique<AddCommand>();

    std::ofstream file("hello_1.txt");

    file << "hello world";

    file.close();

    std::vector<std::string> args = {"hello_1.txt"};

    cmd->execute(args);

    commitManager.createCommit(message);

    EXPECT_EQ(repo.readHead(), "1");

    EXPECT_EQ(std::filesystem::exists(repo.getCommitsPath() / "1"), true);
    
    std::filesystem::path meta = repo.getCommitsPath() / "1/meta";

    EXPECT_EQ(std::filesystem::exists(meta), true);

    std::ifstream metafile(meta);

    std::string metaid, metamessage, parent;

    metafile >> metaid >> parent >> metamessage;

    EXPECT_EQ(metaid, "id:1");

    EXPECT_EQ(parent, "parent:0");

    EXPECT_EQ(metamessage, "message:message");

    std::ofstream file2("hello_2.txt");

    file2 << "hello world";

    file2.close();

    args = {"hello_2.txt"};

    cmd->execute(args);

    commitManager.createCommit(message);

    EXPECT_EQ(repo.readHead(), "2");

    EXPECT_EQ(std::filesystem::exists(repo.getCommitsPath() / "2"), true);
    
    EXPECT_EQ(std::filesystem::exists(repo.getCommitsPath() / "2/meta"), true);

    meta = repo.getCommitsPath() / "2/meta";

    metafile = std::ifstream(meta);

    metafile >> metaid >> parent >> metamessage;

    EXPECT_EQ(metaid, "id:2");

    EXPECT_EQ(parent, "parent:1");

    EXPECT_EQ(metamessage, "message:message");

    std::filesystem::remove_all(".mygit");
}