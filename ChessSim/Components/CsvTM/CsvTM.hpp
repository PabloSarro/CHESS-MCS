// ======================================================================
// \title  CsvTM.hpp
// \author pablo
// \brief  hpp file for CsvTM component implementation class
// ======================================================================

#ifndef ChessSim_CsvTM_HPP
#define ChessSim_CsvTM_HPP

#include "ChessSim/Components/CsvTM/CsvTMComponentAc.hpp"
#include <fstream>
#include <string>

namespace ChessSim {

class CsvTM final : public CsvTMComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct CsvTM object
    CsvTM(const char* const compName);

    //! Destroy CsvTM object
    ~CsvTM();

    //! Helper to open the file
    void openFile(const std::string& filename);

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for user-defined ports
    // ----------------------------------------------------------------------

    //! Handler implementation for SchedIn
    void schedIn_handler(
        const FwIndexType portNum, /*!< The port number*/
        const U32 context /*!< The call order*/
    ) override;

    // ----------------------------------------------------------------------
    // Member variables
    // ----------------------------------------------------------------------
    std::ifstream m_csvFile;
    std::string m_fileName;
    bool m_fileOpen;
};

}  // namespace ChessSim

#endif
