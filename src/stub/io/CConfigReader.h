/*
 * CConfigReader.h
 *
 *  Created on: Aug 7, 2012
 *      Author: gregorytkach
 */

#ifndef CCONFIGREADER_H_
#define CCONFIGREADER_H_

#include "io/IXMLReader.h"
#include "io/SPath.h"

namespace irrgame
{
	namespace io
	{
		class CConfigReader
		{

			public:
				static void readConfig(const path& file);

			private:
				//! Parse <application/>
				static void parseApplication(IXMLReader* xml);
		};
	}
}

#endif /* CCONFIGREADER_H_ */
