//парсер для тестов
//фабричный метод
class AbstractTestGeneration
{
    public:
      virtual AbstractTestGeneration() =0; //конструктор
      virtual AbstractTestGeneration(JsonObject request, Queue* wque) =0;
      virtual ~AbctractTestGeneration() =0; //декструктор

      //преобразование заявки
      virtual void convert(JsonObject &request) =0;
      //возврат тест-кейса
      virtual int sendToWorker(TestCase &tcase) =0;
};
