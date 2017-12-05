class bad_input: public std::exception
{

	protected:
		string msg = "\nInput is invalid! Try again.";

	public:
		explicit bad_input()
		  {}

		virtual ~bad_input() throw (){}

		virtual const char* what() const throw ()
		{
			return msg.c_str();
		}

};

class fileNotOpened : public std::exception
{
protected:
	string msg = "File could not be opened!";

public:
	explicit fileNotOpened() {}
	virtual ~fileNotOpened() throw() {}
	virtual const char * what() const throw()
	{
		return msg.c_str();
	}
};
