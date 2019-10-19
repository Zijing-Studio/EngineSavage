#include"Savage.h"
#include"Loong.h"

class Content
{
public:
	Content() { puts("Creating content."); }
	Content(int x) { puts("Creating content2."); }
	~Content() { puts("Destroying content."); }
	virtual int value() const { return 0; };
	virtual void Print() const { printf("Content Print. %d\n", value()); }
};

class Content2 :public Content
{
public:
	int x;
	Content2(int _x = 0) :Content() { x = _x; printf("%d\n", x); };
	Content2(const Content2& source) { puts("constructing"); x = source.x; }
	~Content2() { printf("%d\n", x); };
	void Print() const { puts("Content2 Print"); }
	int value() const { return x; };
	void test() { Content::Print(); }
	Content2& operator = (const Content2& source) { puts("assigning"); x = source.x; return *this; }
};

class Content3 : public Content
{
public:
	virtual int value() const { return 3075173; };
	virtual void Print() const { printf("Content3 Print. %d\n", value()); }
};

void functest2(const Content& b)
{
	b.Print();
}

void functest()
{
	Content2 c(3);
	//c.test();
	functest2(c);
}

void functest3(Content2 b)
{
	b.test();
}

int seq = 0;

void test2(Content& b)
{
	b.Print();
}

void test()
{
	LVector<Content2>* dict;
	dict = new LVector<Content2>;
	Content* pcontent = &(*dict)[0];
	printf("%p\n", static_cast<Content2*>(pcontent));
	test2(*static_cast<Content3*>(pcontent));
	delete dict;
}



IContent func2(ILoongFunction func)
{
	IContent x;
	x[0].assign(1);
	x[1].assign(2);
	x[2].assign(3);
	return func(x);
}

LoongCode code;
GameWorld world;

#ifdef NONONO
int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd
)
{
	AllocConsole();
	FILE* ihopethisvariablewontaffactothers;
	freopen_s(&ihopethisvariablewontaffactothers, "CON", "r", stdin);
	freopen_s(&ihopethisvariablewontaffactothers, "CON", "w", stdout);
	freopen_s(&ihopethisvariablewontaffactothers, "CON", "w", stderr);
#else
int main()
{
#endif
	//cout << sizeof(world)/1024/1024<<endl;
	ActivateWorld(&world);
	world.gamemap.Init("Map\\test.map");
	world.LoadTemp("Character\\1");
	world.LoadTemp("Character\\2");
	world.Print();
	while (true)
	{
		string order;
		printf(">");
		cin >> order;
		if (order == "summon")
		{
			int tempid, pid, x, y;
			cin >> pid >> tempid >> x >> y;
			GameUnit unit = world.CreateUnitFromTemp(tempid);
			unit.pid = pid;
			unit.pos = Pos(x, y, 0);
			world.Summon(unit, 0);
		}
		else if (order == "attack")
		{
			int fromid, targid;
			cin >> fromid >> targid;
			world.Attack(targid, fromid);
		}
		else if (order == "move")
		{
			int uid, x, y;
			cin >> uid >> x >> y;
			world.Move(uid, Pos(x, y, 0));
		}
		world.Refresh();
		world.Print();
	}
}
/*
summon 1 0 0 0
summon 2 0 1 1
attack 1 2
*/