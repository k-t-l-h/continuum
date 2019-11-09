TEST_F(Container, ContainerBusy)
{
	// some testcase
	TestCase test();
	Container cont();
	
	cont.DoTest(test);
	ASSERT_EQ(cont.Is_free(), false);
}

TEST_F(Container, ContainerFree)
{
	Container cont();
	ASSERT_EQ(cont.Is_free(), true);
}

TEST_F(Container, HasHost)
{
	Container cont();
	ASSERT_EQ(cont.GetContainerHost() != nullptr, true);
}

TEST_F(Container, CorrectTestSent)
{
	// correct testcase
	TestCase test();
	Container cont();
	ASSERT_EQ(cont.DoTest(test), OK);
}

TEST_F(Container, IncorrectTestNotSent)
{
	// incorrect testcase
	TestCase test();
	Container cont();
	ASSERT_EQ(cont.DoTest(test), ERROR);
}

TEST_F(Container, RightAnswer)
{
	// correct answer
	JsonObject answer;
	TestCase test();
	Container cont();
	cont.DoTest(test);
	while(!cont.Is_free())
		sleep(5);
	ASSERT_EQ(cont.GetAnswer, answer);
}
