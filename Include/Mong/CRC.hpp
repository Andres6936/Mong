// Joan Andrés (@Andres6936) Github.

#ifndef MONG_CRC_HPP
#define MONG_CRC_HPP

#include <array>
#include <vector>

#include "Definitions.hpp"

namespace Mong
{

	/**
	 * CRC fields are calculated using standardized
	 * CRC methods with pre and post conditioning,
	 * as defined by ISO 3309 [ISO-3309] and
	 * ITU-T V.42 [ITU-T-V42]. The CRC polynomial
	 * employed is:
	 *
	 * x^32 + x^26 + x^23 + x^22 + x^16 + x^12 + x^11 +
	 * x^10 + x^8 + x^7 + x^5 + x^4 + x^2 + x + 1
	 */
	class CRC
	{

	private:

		/**
		 * Table of CRCs of all 8-bit messages.
		 */
		std::array<UInt32, 256> table;

	public:

		// Construct

		CRC();

		// Methods Invariant

		bool verifyInvariants() const;

		// Methods

		/**
		 * Return the CRC of the bytes (ake. buffer).
		 *
		 * @param _buffer Set of bytes to verify.
		 * @return The cyclic redundancy check of buffer.
		 */
		UInt32 getCyclicRedundancyCheck(const std::vector<std::byte>& _buffer) const;

		void showTable();

	};

}

#endif //MONG_CRC_HPP
