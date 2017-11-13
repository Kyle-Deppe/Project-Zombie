class bad_input: public std::exception
{

	protected:
		string msg = "Input is Invalid! Try again.";

	public:
		explicit bad_input()
		  {}

		virtual ~bad_input() throw (){}

		virtual const char* what() const throw ()
		{
			return msg.c_str();
		}

};
