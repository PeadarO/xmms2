#ifndef XMMSCLIENTPP_LIST_H
#define XMMSCLIENTPP_LIST_H

#include <xmmsclient/xmmsclient.h>
#include <boost/any.hpp>

#include <xmmsclient/xmmsclient++/detail/superlist.h>
#include <xmmsclient/xmmsclient++/typedefs.h>
#include <string>

namespace Xmms
{

	template< typename T >
	class List : public Detail::SuperList
	{

		public:
			List( xmmsc_result_t* result ) :
				Detail::SuperList( result ), contents_()
			{
			}

			virtual ~List()
			{
			}

			const T& operator*()
			{
				constructContents();
				return contents_;
			}

			const T& operator->()
			{
				constructContents();
				return contents_;
			}
			
		private:
			T contents_;

			virtual void constructContents() = 0;

	};

	template<>
	class List< int > : public Detail::SuperList
	{

		public:
			List( xmmsc_result_t* result ) :
				Detail::SuperList( result ), contents_( 0 )
			{
			}

			virtual ~List()
			{
			}

			const int& operator*()
			{
				constructContents();
				return contents_;
			}

			const int& operator->()
			{
				constructContents();
				return contents_;
			}

		private:
			int contents_;

			virtual void constructContents()
			{

				if( constructed_ ) {
					return;
				}

				int temp = 0;
				if( !xmmsc_result_get_int( result_, &temp ) ) {
					// throw something
				}
				contents_ = temp;
				constructed_ = true;
				
			}

	};

	template<>
	class List< unsigned int > : public Detail::SuperList
	{

		public:
			List( xmmsc_result_t* result ) :
				Detail::SuperList( result ), contents_( 0 )
			{
			}

			virtual ~List()
			{
			}

			const unsigned int& operator*()
			{
				constructContents();
				return contents_;
			}

			const unsigned int& operator->()
			{
				constructContents();
				return contents_;
			}

		private:
			unsigned int contents_;

			virtual void constructContents()
			{

				if( constructed_ ) {
					return;
				}

				unsigned int temp = 0;
				if( !xmmsc_result_get_uint( result_, &temp ) ) {
					// throw something
				}
				contents_ = temp;
				constructed_ = true;
				
			}

	};

	template<>
	class List< std::string > : public Detail::SuperList
	{

		public:
			List( xmmsc_result_t* result ) :
				Detail::SuperList( result ), contents_() 
			{
			}

			virtual ~List()
			{
			}

			const std::string& operator*()
			{
				constructContents();
				return contents_;
			}

			const std::string& operator->()
			{
				constructContents();
				return contents_;
			}

		private:
			std::string contents_;

			virtual void constructContents()
			{

				if( constructed_ ) {
					return;
				}

				char* temp = 0;
				if( !xmmsc_result_get_string( result_, &temp ) ) {
					// throw something
				}
				contents_ = std::string( temp );
				constructed_ = true;
				
			}

	};

	typedef std::map< std::string, boost::any > Dict;
	template<>
	class List< Dict > : public Detail::SuperList
	{

		public:
			List( xmmsc_result_t* result ) :
				Detail::SuperList( result ), contents_() 
			{
			}

			virtual ~List()
			{
			}

			const Dict& operator*()
			{
				constructContents();
				return contents_;
			}

			const Dict* operator->()
			{
				constructContents();
				return &contents_;
			}

		private:
			Dict contents_;

			virtual void constructContents()
			{
				if( constructed_ ) {
					return;
				}

				xmmsc_result_dict_foreach( result_, Detail::dict_foreach,
				                           static_cast< void* >(&contents_) );

				constructed_ = true;
												
			}

	};
}

#endif // XMMSCLIENTPP_LIST_H
