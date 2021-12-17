# Helper functions for better debugging with gdb

define trace-function
if $arg0
    break $arg0
    commands
        continue
        end
    end
end
document trace-function
    Print a message every time a function is called
end
