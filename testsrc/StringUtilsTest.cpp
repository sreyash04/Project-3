#include <gtest/gtest.h>
#include "StringUtils.h"

TEST(StringUtilsTest, SliceTest){
    std::string Base= "Hello";
    EXPECT_EQ(StringUtils::Slice(Base,0),"Hello");
    EXPECT_EQ(StringUtils::Slice(Base,1),"ello");
    EXPECT_EQ(StringUtils::Slice(Base,2),"llo");
    EXPECT_EQ(StringUtils::Slice(Base,5),"");
}

TEST(StringUtilsTest, Capitalize){
    std::string Base = "Hello";

    EXPECT_EQ(StringUtils::Capitalize(Base),"Hello");
    EXPECT_EQ(StringUtils::Capitalize(std::string()),"");
    EXPECT_EQ(StringUtils::Capitalize(" Hello")," hello");
    EXPECT_EQ(StringUtils::Capitalize(" 242/'?@")," 242/'?@");
    EXPECT_EQ(StringUtils::Capitalize("hello"),"Hello");
    EXPECT_EQ(StringUtils::Capitalize("HELLO"),"Hello");
}

TEST(StringUtilsTest, Upper){
    EXPECT_EQ(StringUtils::Upper(" Hello")," HELLO");
    EXPECT_EQ(StringUtils::Upper("hello"),"HELLO");
    EXPECT_EQ(StringUtils::Upper(" 9He4llo434")," 9HE4LLO434");
    EXPECT_EQ(StringUtils::Upper(std::string()),"");
}

TEST(StringUtilsTest, Lower){
    EXPECT_EQ(StringUtils::Lower(" Hello")," hello");
    EXPECT_EQ(StringUtils::Lower("HELLO"),"hello");
    EXPECT_EQ(StringUtils::Lower(" 9hE4LLO434")," 9he4llo434");
    EXPECT_EQ(StringUtils::Lower(std::string()),"");
}

TEST(StringUtilsTest, LStrip){
    EXPECT_EQ(StringUtils::LStrip(" Hello"),"Hello");
    EXPECT_EQ(StringUtils::LStrip("     H ello  "),"H ello  ");
    EXPECT_EQ(StringUtils::LStrip("Hello   "),"Hello   ");
    EXPECT_EQ(StringUtils::LStrip("Hel5lo"),"Hel5lo");
    EXPECT_EQ(StringUtils::LStrip("   343fj3 "),"343fj3 ");
    EXPECT_EQ(StringUtils::LStrip(std::string()),"");
}

TEST(StringUtilsTest, RStrip){
    EXPECT_EQ(StringUtils::RStrip("Hello "),"Hello");
    EXPECT_EQ(StringUtils::RStrip("     H ello   "),"     H ello");
    EXPECT_EQ(StringUtils::RStrip("   Hello"),"   Hello");
    EXPECT_EQ(StringUtils::RStrip("Hel5lo"),"Hel5lo");
    EXPECT_EQ(StringUtils::RStrip(std::string()),"");
    EXPECT_EQ(StringUtils::RStrip("   343fj3 "),"   343fj3");
}

TEST(StringUtilsTest, Strip){
    EXPECT_EQ(StringUtils::Strip(" Hello "),"Hello");
    EXPECT_EQ(StringUtils::Strip("     H ello   "),"H ello");
    EXPECT_EQ(StringUtils::Strip("   Hello"),"Hello");
    EXPECT_EQ(StringUtils::Strip("Hel5lo  "),"Hel5lo");
    EXPECT_EQ(StringUtils::Strip(std::string()),"");
    EXPECT_EQ(StringUtils::Strip("   343fj3 "),"343fj3");
}

TEST(StringUtilsTest, Center){
    EXPECT_EQ(StringUtils::Center(" Hello", 8),"  Hello ");
    EXPECT_EQ(StringUtils::Center("Hello", 10),"  Hello   ");
    EXPECT_EQ(StringUtils::Center("     Hello", 10),"     Hello");
    EXPECT_EQ(StringUtils::Center("Hello", 10,'-'),"--Hello---");
    EXPECT_EQ(StringUtils::Center(std::string(),0),"");
}

TEST(StringUtilsTest, LJust){
    EXPECT_EQ(StringUtils::LJust(" Hello", 8)," Hello  ");
    EXPECT_EQ(StringUtils::LJust("Hello", 10),"Hello     ");
    EXPECT_EQ(StringUtils::LJust("     Hello", 10),"     Hello");
    EXPECT_EQ(StringUtils::LJust("Hello", 10,'-'),"Hello-----");
    EXPECT_EQ(StringUtils::LJust(std::string(),0),"");
}

TEST(StringUtilsTest, RJust){
    EXPECT_EQ(StringUtils::RJust(" Hello", 8),"   Hello");
    EXPECT_EQ(StringUtils::RJust("Hello", 10),"     Hello");
    EXPECT_EQ(StringUtils::RJust("Hello     ", 10),"Hello     ");
    EXPECT_EQ(StringUtils::RJust("Hello", 10,'-'),"-----Hello");
    EXPECT_EQ(StringUtils::RJust(std::string(),0),"");
}

TEST(StringUtilsTest, Replace){
    EXPECT_EQ(StringUtils::Replace("Whats up Dog", "Dog", "Dawg"),"Whats up Dawg");
    EXPECT_EQ(StringUtils::Replace("H", "H", "A"),"A");
    EXPECT_EQ(StringUtils::Replace("Whats up Do g", "Dog", "Dawg"),"Whats up Do g");
    EXPECT_EQ(StringUtils::Replace("Whats up Do8g", "Dog", "Dawg"),"Whats up Do8g");
    EXPECT_EQ(StringUtils::Replace("Whats up Dog", "Dog", ""),"Whats up ");
    EXPECT_EQ(StringUtils::Replace(std::string(),"",""),"");
    EXPECT_EQ(StringUtils::Replace("Whats up Do&g", "Dog", "Dawg"),"Whats up Do&g");
    EXPECT_EQ(StringUtils::Replace("Whats up Do8g", "Do8g", "Dawg"),"Whats up Dawg");
    EXPECT_EQ(StringUtils::Replace("Whats up Dog.", "Dog", "Dawg"),"Whats up Dawg.");
    EXPECT_EQ(StringUtils::Replace("Whats up Dad Dog.", "Dog", "Dawg"),"Whats up Dad Dawg.");
    EXPECT_EQ(StringUtils::Replace("Whats up Doggy.", "Dog", "Dawg"),"Whats up Dawggy.");
    EXPECT_EQ(StringUtils::Replace("Whats up Doggy.", "Dog ", "Dawg "),"Whats up Doggy.");
    EXPECT_EQ(StringUtils::Replace(std::string(1000, 'a'), "a", "b"), std::string(1000, 'b'));
    EXPECT_EQ(StringUtils::Replace("Hello Hello", "Hello", "Hi"), "Hi Hi");
    EXPECT_EQ(StringUtils::Replace("Short", "Short", "Longer"), "Longer");
    EXPECT_EQ(StringUtils::Replace("Dog", "", "!"), "!D!o!g!");
}

TEST(StringUtilsTest, Split){
    EXPECT_EQ((StringUtils::Split("hi,hey,hello", ",")), (std::vector<std::string>{"hi", "hey", "hello"})); //Partially AI Generated see README AI 2
    EXPECT_EQ((StringUtils::Split("hi hey hello", " ")), (std::vector<std::string>{"hi", "hey", "hello"}));
    EXPECT_EQ((StringUtils::Split("hi hey hello")), (std::vector<std::string>{"hi", "hey", "hello"}));
    EXPECT_EQ((StringUtils::Split("")), (std::vector<std::string>{}));
    EXPECT_EQ((StringUtils::Split("hiheyhello", ",")), (std::vector<std::string>{"hiheyhello"}));
    EXPECT_EQ((StringUtils::Split("hi,,hey,hello", ",")), (std::vector<std::string>{"hi", "", "hey", "hello"}));
    EXPECT_EQ((StringUtils::Split(",hi,hey,hello", ",")), (std::vector<std::string>{"", "hi", "hey", "hello"}));
    EXPECT_EQ((StringUtils::Split("hi,hey,hello,", ",")), (std::vector<std::string>{"hi", "hey", "hello", ""}));
    EXPECT_EQ((StringUtils::Split("hi,hey hey", ",")), (std::vector<std::string>{"hi", "hey hey"}));
    EXPECT_EQ((StringUtils::Split("222", "2")), (std::vector<std::string>{"", "", "", ""}));
    EXPECT_EQ((StringUtils::Split("hi,,hey,,hello", ",,")), (std::vector<std::string>{"hi", "hey", "hello"}));
}

TEST(StringUtilsTest, Join){
    EXPECT_EQ(StringUtils::Join(",", {"hi", "hey", "hello"}), "hi,hey,hello");
    EXPECT_EQ(StringUtils::Join("", {"hi", "hey", "hello"}), "hiheyhello");
    EXPECT_EQ(StringUtils::Join(" ", {"hi", "hey", "hello"}), "hi hey hello");
    EXPECT_EQ(StringUtils::Join(",", {"hi"}), "hi");
    EXPECT_EQ(StringUtils::Join(",", {}), "");
    EXPECT_EQ(StringUtils::Join(" , ", {"hi", "hey", "hello"}), "hi , hey , hello");
    EXPECT_EQ(StringUtils::Join(",", {"hi,1", "hey,2", "hello,3"}), "hi,1,hey,2,hello,3");

}

TEST(StringUtilsTest, ExpandTabs){
    EXPECT_EQ(StringUtils::ExpandTabs("hi hey", 4), "hi hey");
    EXPECT_EQ(StringUtils::ExpandTabs("hi\they", 4), "hi  hey");
    EXPECT_EQ(StringUtils::ExpandTabs("\thi\they", 4), "    hi  hey");
    EXPECT_EQ(StringUtils::ExpandTabs("hi\they", 2), "hi  hey");
    EXPECT_EQ(StringUtils::ExpandTabs("hi\they\t?", 4), "hi  hey ?");
    EXPECT_EQ(StringUtils::ExpandTabs("hi\t\they", 4), "hi      hey");
    EXPECT_EQ(StringUtils::ExpandTabs("hi\they", 8), "hi      hey");
    EXPECT_EQ(StringUtils::ExpandTabs("", 4), "");
    EXPECT_EQ(StringUtils::ExpandTabs("hi\they", 1), "hi hey");
}

TEST(StringUtilsTest, EditDistance){
    EXPECT_EQ(StringUtils::EditDistance("hey", "hey", false), 0);
    EXPECT_EQ(StringUtils::EditDistance("hello", "world", false), 4);
    EXPECT_EQ(StringUtils::EditDistance("", "hello", false), 5);
    EXPECT_EQ(StringUtils::EditDistance("hi", "hello", false), 4);
    EXPECT_EQ(StringUtils::EditDistance("Hey", "hey", true), 0);
    EXPECT_EQ(StringUtils::EditDistance("hello", "ello", false), 1);
    EXPECT_EQ(StringUtils::EditDistance("Hello", "hello", false), 1);
    EXPECT_EQ(StringUtils::EditDistance("hello", "helol", false), 2);
    EXPECT_EQ(StringUtils::EditDistance("hey", "hay", false), 1);
    EXPECT_EQ(StringUtils::EditDistance("hello", "heello", false), 1);
    EXPECT_EQ(StringUtils::EditDistance("kitten", "fitting", false), 3);
}
