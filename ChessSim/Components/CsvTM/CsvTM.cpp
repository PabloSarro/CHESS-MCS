// ======================================================================
// \title  CsvTM.cpp
// \author pablo
// \brief  cpp file for CsvTM component implementation class
// ======================================================================

#include "ChessSim/Components/CsvTM/CsvTM.hpp"
#include <Fw/Logger/Logger.hpp>
#include "Fw/Types/BasicTypes.hpp"
#include <cstdlib> // for std::stof

namespace ChessSim {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

CsvTM ::CsvTM(const char* const compName) :
    CsvTMComponentBase(compName),
    m_fileOpen(false)
{
    // Hardcoded path for simulation
    this->m_fileName = "/tmp/sim_data.csv";
}

CsvTM ::~CsvTM() {
    if (this->m_fileOpen) {
        this->m_csvFile.close();
    }
}

// ----------------------------------------------------------------------
// Helper Methods
// ----------------------------------------------------------------------

void CsvTM::openFile(const std::string& filename) {
    this->m_csvFile.open(filename.c_str());
    if (this->m_csvFile.is_open()) {
        this->m_fileOpen = true;
    } else {
        this->m_fileOpen = false;
        // Log a warning so it's visible in GDS / logs
        Fw::LogStringArg logString(filename.c_str());
        this->log_WARNING_HI_FileOpenFail(logString);
    }
}

// ----------------------------------------------------------------------
// Handler implementations for user-defined ports
// ----------------------------------------------------------------------

void CsvTM ::schedIn_handler(const FwIndexType portNum, const U32 context) {
    // 1. Ensure file is open
    if (!this->m_fileOpen) {
        this->openFile(this->m_fileName);
        return;
    }

    // 2. Read a line
    std::string line;
    if (std::getline(this->m_csvFile, line)) {
        try {
            // 3. Parse Float and send Telemetry
            float value = std::stof(line);
            this->tlmWrite_CsvValue(static_cast<F32>(value));
            printf("[CsvTM] Read success: %f\n", value);
        } catch (...) {
            // Ignore parsing errors (e.g. empty lines)
            printf("[CsvTM] ERROR: Could not parse float from line: '%s'\n", line.c_str());
        }
    } else {
        // 4. End of file? Rewind to start loop
        this->m_csvFile.clear(); // Clear EOF flag
        this->m_csvFile.seekg(0);
        printf("[CsvTM] End of file reached. Rewinding.\n");
    }
}

}  // namespace ChessSim