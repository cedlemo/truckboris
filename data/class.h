class MyClass
{
  public:
    MyClass() {}
    ~MyClass() {}
    bool isTrue() const;
    bool isFalse() const;
  private:
    bool m_attrib;
};

bool MyClass::isTrue() const
{
  return true;
}

bool MyClass::isFalse() const
{
  return false;
}
class MyOtherClass
{
  MyOtherClass() {}
  ~MyOtherClass() {}
};
