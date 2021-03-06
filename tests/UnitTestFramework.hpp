#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <string>


//template <typename First, typename Second>
//std::ostream& operator << (std::ostream& out, const std::pair<First, Second>& p);

template<typename T>
bool operator==(const std::set<T>&, const std::set<T>& );

template<typename T>
bool operator==(const std::pair<T, T>&, const std::pair<T, T>&);

template <typename Collection>
std::string Join(const Collection& c, const std::string& d);

template <typename T>
std::ostream& operator << (std::ostream& out, const std::vector<T>& vi);

template <typename Key, typename Value>
std::ostream& operator << (std::ostream& out, const std::map<Key, Value>& m);

template <typename T>
std::ostream& operator << (std::ostream& out, const std::set<T>& s);

template<class T, class U>
void AssertEqual(const T& t, const U& u, const std::string& hint);

void Assert(bool cond, const std::string& hint);


class TestRunner
{
public:
    TestRunner();
    ~TestRunner();
    template<class TestFunction>
    void RunTest(TestFunction test_function,
                 const std::string& test_function_name);

private:
    int fail_count;
};


//template <typename First, typename Second>
//std::ostream& operator << (std::ostream& out, const std::pair<First, Second>& p)
//{
    //return out << '(' << p.first << ", " << p.second << ')';
//}

template <typename Collection>
std::string Join(const Collection& c, const std::string& d)
{
    std::stringstream ss;
    bool first = true;
    for (const auto& i : c) {
        if (!first) {
            ss << d;
        }
        first = false;
        ss << i;
    }
    return ss.str();
}


template <typename T>
std::ostream& operator << (std::ostream& out, const std::vector<T>& vi)
{
    return out << '[' << Join(vi, ", ") << ']';
}

template <typename Key, typename Value>
std::ostream& operator << (std::ostream& out, const std::map<Key, Value>& m)
{
    return out << '{' << Join(m, ", ") << '}';
}


template <typename T>
std::ostream& operator << (std::ostream& out, const std::set<T>& s)
{
    return out << '{' << Join(s, ", ") << '}';
}


template<typename T>
bool operator==(const std::pair<T, T>& lhs, const std::pair<T, T>& rhs)
{
    return (lhs.first == rhs.first && lhs.second == rhs.second);
}

template<typename T>
bool operator==(const std::set<T>& lhs, const std::set<T>& rhs)
{
    return (lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(),
                                                   rhs.begin()));
}


template<class T, class U>
void AssertEqual(const T& t, const U& u, const std::string& hint)
{
    if (t != u)
    {
        std::ostringstream os;
        os << "Assertion failed: " << t << " != " << u << " Hint: " << hint;

        throw std::runtime_error(os.str());
    }
}


template<class TestFunction>
void TestRunner::RunTest(TestFunction test_function,
                         const std::string& test_function_name)
{

    try
    {
        test_function();
        std::cerr << test_function_name << " OK" << std::endl;
    }
    catch (std::runtime_error& ex)
    {
        ++fail_count;
        std::cerr << test_function_name << " fail: " << ex.what() << std::endl;
    }
}

//bool operator==(const std::set<std::pair<char, char>>& lhs, const std::set<std::pair<char, char>>& rhs)
//{
//    return lhs.size() == rhs.size()
//            && equal(lhs.begin(), lhs.end(), rhs.begin());
//}
