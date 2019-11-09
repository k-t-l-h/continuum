//общий интерфейс для тесткейсов
class TestCase
{
  public:
    virtual TestCase() =0;
    virtual ~TestCase() =0;
    int id;

};
