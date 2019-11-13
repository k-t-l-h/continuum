//парсер для тестов
//фабричный метод
class AbstractTestGeneration
{
    public:
      virtual AbstractTestGeneration() =0; //конструктор
      virtual AbstractTestGeneration(const JsonObject &req, Queue<TestCase*> &wque)) =0;
      virtual ~AbctractTestGeneration() =0; //декструктор

      //преобразование заявки
      virtual void convert() =0;
      //возврат тест-кейса
      virtual int sendToWorker() =0;
};
