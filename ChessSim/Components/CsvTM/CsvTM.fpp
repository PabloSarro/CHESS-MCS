module ChessSim {
    @ Reads CSV Simulation Data
    active component CsvTM {

        # ----------------------------------------------------------------------
        # General Ports
        # ----------------------------------------------------------------------

        @ Port to receive the schedule tick (the "clock")
        async input port schedIn: Svc.Sched

        # ----------------------------------------------------------------------
        # Telemetry
        # ----------------------------------------------------------------------

        @ The value read from the CSV file
        telemetry CsvValue: F32 id 0

        # ----------------------------------------------------------------------
        # Events
        # ----------------------------------------------------------------------

        @ File could not be opened
        event FileOpenFail(filename: string) severity warning high id 0x01 format "Failed to open file {}"

        # ----------------------------------------------------------------------
        # Special Ports & Standard Imports
        # ----------------------------------------------------------------------

        @ Port for requesting the current time
        time get port timeCaller

        @ Enables command handling
        import Fw.Command

        @ Enables event handling
        import Fw.Event

        @ Enables telemetry channels handling
        import Fw.Channel

        @ Port to return the value of a parameter
        param get port prmGetOut

        @Port to set the value of a parameter
        param set port prmSetOut

    }
}