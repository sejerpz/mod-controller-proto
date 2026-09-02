/*
************************************************************************************************************************
*           MOD Devices Controller Protocol Definitions
************************************************************************************************************************
*/

/*
********************************
    SHARED DEVICE COMMANDS
********************************
*/

// ping
//response: `r 0`
//HMI action: nothing, just respond back
//HOST action: -
#define CMD_PING                      "pi"

// say <message>
//response: `<message>`
#define CMD_SAY                       "say %s ..."

// led <led_id> <red> <green> <blue>
//response: `r 0`
//HMI action: turn on LED
//HOST action: TODO, TURN ON PEAKMETER LEDS (if ever needed)
#define CMD_LED                       "l %i %i %i %i ..."

// brightness <o to 4>
//response: `r 0`
//HMI action: change display brightness
//HOST action: -
#define CMD_DISP_BRIGHTNESS           "displ_bright %i"

// glcd_text <glcd_id> <x_pos> <y_pos> <text>
//response: `r 0`
//HMI action: display the line text <text> at x y
//HOST action: -
#define CMD_GLCD_TEXT                 "glcd_text %i %i %i %s"

// glcd_dialog <content>
//response: `r 0`
//HMI action: display the text <text> in a popup
//HOST action: 0
#define CMD_GLCD_DIALOG               "glcd_dialog %s"

// glcd_draw <glcd_id> <x_pos> <y_pos> <data>
//response: `r 0`
//HMI action: display the data <data> at x y
//HOST action: -
#define CMD_GLCD_DRAW                 "glcd_draw %i %i %i %s"

// ui_con
//response: `r 0`
//HMI action: now aware the web-ui is connected
//HOST action: -
#define CMD_GUI_CONNECTED             "uc"

// ui_dis
//response: `r 0`
//HMI action: now aware the web-ui is disconnected
//HOST action: -
#define CMD_GUI_DISCONNECTED          "ud"

// control_add <hw_id> <label> <control_prop> <unit> <value> <max> <min> <steps>
//             [scale_point_count] [scale_point_flag] [scale_point_index] {[scale_point1_label] [scale_point1_value]}...
//response: `r 0`
//HMI action: assign a new hw control
//HOST action: -
#define CMD_CONTROL_ADD               "a %i %s %i %s %f %f %f %i %i ..."

// control_rm <hw_id>
//response: `r 0`
//HMI action: unassign a hw control
//HOST action: -
#define CMD_CONTROL_REMOVE            "d %i ..."

// control_get <hw_id>
//response: `s %i %f`
//HMI action: -
//HOST action: returns the assigned control value via control_set
#define CMD_CONTROL_GET               "g %i"

// control_set <hw_id><value>
//response: `r 0`
//HMI action: sends assigned control data
//HOST action: sends assigned control data
#define CMD_CONTROL_SET               "s %i %f"

// next control page <hw_id> <prop bitmask> <page index id>
//response: `a %i %s %i %s %f %f %f %i %i ...`
//HMI action: -
//HOST action: sends back a control_add command with new control page data
#define CMD_CONTROL_PAGE              "ncp %i %i %i"

// initial_state <amount of pb's> <page_min> <page_max> <bank_id> <bank_flags> <pb_index> [current_pedalboards_list: index, flags, quoted title]
//response: `r 0`
//HMI action: save initial pedalboard and bank data in static memory
//HOST action: -
#define CMD_INITIAL_STATE             "is %i %i %i %i %i %i ..."

// banks <direction> <current banks hover id>
//response: `new banks list, with updated items` (uid:int, flags, quoted title)
//HMI action: -
//HOST action: returns a new page of banks
#define CMD_BANKS                     "b %i %i"

// bank new <bank_name>
//response: -
//HMI action: -
//HOST action: creates a new bank
#define CMD_BANK_NEW                  "bn %s ..."

// bank delete <bank_id>
//response: -
//HMI action: -
//HOST action: deletes indicated bank
#define CMD_BANK_DELETE               "bd %i"

// add pedalboards to bank <bank_uid_to_add_to> <bank_uid_pbs_originate_from> <pb_uids:str>
//response: -
//HMI action: -
//HOST action: add the pb uids to the bank
//             add all the pbs from a bank if bank_id_pbs_originate_from == -1, in that case
//             bank uids are passed
#define CMD_ADD_PBS_TO_BANK           "ba %i %i %s ..."

// reorder the pb within a bank <bank_uid> <pb_index_to_move> <index_to_move_to>
//response: -
//HMI action: -
//HOST action: reorder the pb in a bank
#define CMD_REORDER_PBS_IN_BANK       "br %i %i %i"

// pedalboards <up/down page> <current page index> <bank_uid>
//response: `new pedalboard list, with updated items` (uid:str, flags, quoted title)
//HMI action: -
//HOST action: returns a new page of pedalboards
#define CMD_PEDALBOARDS               "p %i %i %i"

//set the name of the current pedalboard on the device display
//response: `r 0`
//HMI action: save and possibly display the new pedalboard name
//HOST action: -
#define CMD_PEDALBOARD_NAME_SET       "pn %s ..."

//set the current active pedalboard within the current bank, send whenever it changed outside of the HMI
//response: `r 0`
//HMI action: change the active pedalboard and possibly request a new list
//HOST action: -
#define CMD_PEDALBOARD_CHANGE      "pchng %i"

// pedalboard <bank_uid:int> <pb_uid:str>
//response: `r 0`
//HMI action: -
//HOST action: loads the requested pedalboard
#define CMD_PEDALBOARD_LOAD           "pb %i %s"

// pedalboard_reset
//response: `r 0`
//HMI action: -
//HOST action: resets the pedalboard to the last saved state
#define CMD_PEDALBOARD_RESET          "pr"

// pedalboard_save
//response: `r 0`
//HMI action: -
//HOST action: saves the pedalboard in the current state
#define CMD_PEDALBOARD_SAVE           "ps"

//save current setup as new pedalboard
//response: `r 0`
//HMI action:
//HOST action: saves the pb, if the name already excists, return -1
#define CMD_PEDALBOARD_SAVE_AS        "psa %s ..."

//clear both snapshots and control changes
//response: `r 0`
//HMI action: clear all pedalboard related items
//HOST action: -
#define CMD_PEDALBOARD_CLEAR          "pcl"

// pedalboard_loading_begin / pedalboard_loading_end
// The two ends of a pedalboard being loaded, whoever asked for it -- the web UI, the
// footswitches, a bank change or the boot. Not a bracket around CMD_PEDALBOARD_LOAD, which
// is the HMI asking for one: these are the host saying one is under way, from any source. Everything between them is a board in pieces:
// plugins arriving one at a time, cables and addressings following. Anything on the HMI
// that is a view onto the board has to stand down for the duration, and anything that
// wants to say so to the user has its two edges here.
//response: `r 0`
//HMI action: leaves the builder, which is a view onto the board being replaced
//HOST action: -
#define CMD_PEDALBOARD_LOADING_BEGIN     "plb"

//response: `r 0`
//HMI action: -
//HOST action: -
#define CMD_PEDALBOARD_LOADING_END       "ple"

// pedalboard delete <bank_uid> <pb_index>
//response: -
//HMI action: -
//HOST action: deletes indicated pedalboard
#define CMD_PEDALBOARD_DELETE         "pbd %i %i"

// reorder the snapshot within a pedalboard <snapshot_to_move_uid> <index_to_move_to>
//response: -
//HMI action: -
//HOST action: reorder the pb in a bank
#define CMD_REORDER_SSS_IN_PB         "sr %i %i"

// snapshots <up/down page> <current page index>
//response: `new snapshot list, with updated items`
//HMI action: -
//HOST action: returns a new page of pedalboards
#define CMD_SNAPSHOTS                 "ssg %i %i"

//set the name of the current snapshot on the device display <snapshot_id> <snapshot_name>
//response: `r 0`
//HMI action: save and possibly display the new snapshot name
//HOST action: -
#define CMD_SNAPSHOT_NAME_SET         "sn %i %s ..."

// snapshot <snapshot_uid>
//response: `r 0`
//HMI action: -
//HOST action: loads the requested snapshot
#define CMD_SNAPSHOTS_LOAD            "ssl %i"

// snapshot save
//response: `r 0`
//HMI action: -
//HOST action: saves the currently active snapshot
#define CMD_SNAPSHOTS_SAVE            "sss"

//save the current control config as a snapshot
//response: `r 0`
//HMI action:
//HOST action: saves the snapshot, if the name already excists, return -1
#define CMD_SNAPSHOT_SAVE_AS          "ssa %s ..."

// bank snapshot <snapshot_id>
//response: -
//HMI action: -
//HOST action: deletes indicated snapshot
#define CMD_SNAPSHOT_DELETE           "ssd %i"

// tuner <frequency> <note> <cents>
//response: `r 0`
//HMI action: adjust the tuner screen to new data
//HOST action: -
#define CMD_TUNER                     "ts %f %s %i"

// tuner on
//response: `r 0`
//HMI action: -
//HOST action: turn on the tuner
#define CMD_TUNER_ON                  "tn"

// tuner off
//response: `r 0`
//HMI action: -
//HOST action: turn off the tuner
#define CMD_TUNER_OFF                 "tf"

// tuner_input <input>
//response: `r 0`
//HMI action: -
//HOST action: changes the tuner input source
#define CMD_TUNER_INPUT               "ti %i"

// tuner_reference_frequency <frequency>
//response: `r 0`
//HMI action: -
//HOST action: changes the tuner A reference frequency
#define CMD_TUNER_REF_FREQ            "tr %i"

// reboot in restore mode
//response: `r 0`
//HMI action: boot into restore mode
//HOST action: -
#define CMD_RESTORE                   "restore"

// send display data to mod-ui <index 0 to 8> <data>
//response: `r 0`
//HMI action: send display data to mod-ui, 8 messages containing 128 hexadecimal numbers representing 8 vertical pixels
//HOST action: generate a screenshot to be used for manuals and wiki articles
#define CMD_SCREENSHOT               "screenshot %i %s"

// resp <status> ...
//response: -
//HMI action: -
//HOST action: -
#define CMD_RESPONSE                  "r %i ..."

// convenience macros
#define CMD_RESPONSE_NONE             "r %i"
#define CMD_RESPONSE_INT              "r %i %i"
#define CMD_RESPONSE_STR              "r %i %s"

/*
********************************
    SHARED MENU COMMANDS
********************************
Almost all menu items are also setable via the MENU_ITEM_CHANGE command, but some have their dedicated
*/

//change a menu setting [uint8_t]<menu_item_id> [uint16_t]<menu_item_value>
//response: `r 0`
//HMI action: change the setting in the menu acourding to the settings ID
//HOST action: change the setting in the system acourding to the settings ID
//if there is only 1 argument given, the value of that argument will be returned
#define CMD_MENU_ITEM_CHANGE          "c %i %i ..."

//get profile data command <int profile>
//response: `r 0`
//HMI action: -
//HOST action: loads the selected user profile
#define CMD_PROFILE_LOAD              "upr %i"

//store the current profile in mod-ui
//response: `r 0`
//HMI action: -
//HOST action: store the selected user profile with current settings
#define CMD_PROFILE_STORE             "ups %i"

//request the next page <page_to_load>
//response: `r 0`
//HMI action: -
//HOST action: reassigns all controls to the next control page when available
#define CMD_NEXT_PAGE                 "lp %i"

//clear all HMI EEPROM settings
//response: `r 0`
//HMI action: clear internal EEPROM settings and reset default value's
//HOST action: -
#define CMD_RESET_EEPROM              "reset_eeprom"

// change audio frame size <new_size>
//response: `r 0`
//HMI action: -
//HOST action: current audio frame size
#define CMD_AUDIO_FRAME_SIZE          "afs %i"

/*
********************************
    Duo Specific commands
********************************
*/

//the HMI is ready to boot
#define CMD_DUO_BOOT                  "boot %i %i %s ..."

//enable footswitch bank navigation [uint8_t]<foot>
//response: `r 0`
//HMI action: -
//HOST action: turns on bank navigation on footswitch <foot>
#define CMD_DUO_FOOT_NAVIG            "fn %i"

//TODO, IS THIS COMMAND STILL USED?!?
// bank_config <hw_id> <function>
//response: `r 0`
//HMI action: turns on bank navigation on footswitch <hw_id> with <function>
//HOST action: -
#define CMD_DUO_BANK_CONFIG           "bc %i %i"

// control_next <hw_id>
//response: `r 0`
//HMI action: -
//HOST action: reassigns control <hw_id> with a new actuator
#define CMD_DUO_CONTROL_NEXT          "n %i"

// control_index_set <hw_id> <current_index> <total_index>
//response: `r 0`
//HMI action: saves and possibly displays the control indexes for control <hw_id>
//HOST action: -
#define CMD_DUO_CONTROL_INDEX_SET     "si %i %i %i"

/*
********************************
    DuoX Specific commands
********************************
*/

//the HMI is ready to boot
#define CMD_DUOX_BOOT                 "boot %i %i %s ..."

//save a snapshot <snapshot_id>
//response: `r 0`
//HMI action: -
//HOST action: save all controls as a snapshot with index <snapshot_id>
#define CMD_DUOX_SNAPSHOT_SAVE        "ss %i"

//load a snapshot <snapshot_id>
//response: `r 0`
//HMI action: -
//HOST action: set all controls to a snapshot with index <snapshot_id>
#define CMD_DUOX_SNAPSHOT_LOAD        "sl %i"

// TODO is this really used??
//clear a snapshot <snapshot_id>
//response: `r 0`
//HMI action: -
//HOST action: clear a snapshot with index <snapshot_id>
#define CMD_DUOX_SNAPSHOT_CLEAR       "sc"

//let the HMI know how many pages there are
//response: `r 0`
//HMI action: turn on scrolling through a selection of pages
//HOST action: -
#define CMD_DUOX_PAGES_AVAILABLE      "pa %i %i %i %i %i %i"

//sets the display contrast on the HMI <display_id> <contrast value between 0 and 100>
//response: `r 0`
//HMI action: changes display contrast
//HOST action: -
#define CMD_DUOX_SET_CONTRAST      "s_contrast %i %i"

//notify the HMI of the EXP mode change
//response: `r 0`
//HMI action: gives user popup regarding the I/O chagne
//HOST action: -
#define CMD_DUOX_EXP_OVERCURRENT      "exp_overcurrent"

/*
********************************
    Dwarf Specific commands
********************************
*/

//report to UI that a subpage changed for control <hw_id> <subpage>
//response: `r 0`
//HMI action: -
//HOST action: reassigns control <hw_id> with the actuator from the requested page
#define CMD_DWARF_CONTROL_SUBPAGE     "cs %i %i"

//let the HMI know how many pages there are
//response: `r 0`
//HMI action: turn on scrolling through a selection of pages
//HOST action: -
#define CMD_DWARF_PAGES_AVAILABLE     "pa %i %i %i %i %i %i %i %i"


// builder get # control from start to count 
// <plugin_instance_id>: instance id of the plugin in the pedalboard
// <constrol start index>: first index to get
// <control count>: number of controls to get
// response: `r 1 <number of controls>`
//HMI action: -
//HOST action: sends back a control_add command with new control data
#define CMD_BUILDER_CONTROL_LIST      "bctl %s %i %i"

// control_set <hw_id><value>
//response: `r 0`
//HMI action: sends assigned control data
//HOST action: sends assigned control data
#define CMD_BUILDER_CONTROL_SET        "bcts %i %f"


// next_control_page <hw_id> <prop bitmask> <current page index id>
//response: `r 1...`
//HMI action: get next control page data (e.g. options or presets)
//HOST action: sends aa list of options relevant to the current page index and
//             and the prop bitmask (e.g. page next / page prev)
#define CMD_BUILDER_CONTROL_PAGE        "bctp %i %i %i"


// builder pedalboard minimap <props bitmask> <focus node id>
// <props bitmask>: FLAG_PAGINATION_INITIAL_REQ asks for the default window and ignores <focus node id>
// <focus node id>: the node the window is centred on, as numbered by the previous display list
//response: `r 1 <display list>`
//HMI action: parses the display list and draws the pedalboard graph
//HOST action: sends back the display list for the window around <focus node id>
#define CMD_BUILDER_PLUGIN_MAP        "bplm %i %i"


// builder connections of one box <node id> <signal type bitmask>
// <node id>: as numbered by the display list; <bitmask>: MINIMAP_AUDIO|MIDI|CV, 0 for all
// A line is one connection between two boxes and not one cable: a stereo pair is one line.
// Each line ends with the cables it stands for, as pairs of port names, feeding end first.
// CMD_BUILDER_CONNECTION_TARGETS and CMD_BUILDER_CONNECTION_PORTS answer in the same shape with a
// count of zero, so one parser on the HMI reads all three.
// response: `r 1 <count> [<i|o> <other node id> <type bitmask> <label> <pair count>
//                         [<source port> <sink port>] * pair count] * count`
//           `i` is a cable into this box, `o` one out of it
//HMI action: fills the connection menu of the selected box
//HOST action: -
#define CMD_BUILDER_CONNECTION_LIST        "bcnl %i %i"

// builder drop the cables between two boxes <from node id> <to node id> <signal type bitmask>
// One line of the picture can stand for several cables -- a stereo pair is one line -- and
// all of them go.
// response: `r 1 <number of cables dropped>`
//HMI action: -
//HOST action: disconnects the ports and tells the web UI
#define CMD_BUILDER_CONNECTION_DELETE        "bcnd %i %i %i"


// builder boxes one of our ports could meet <node id> <bitmask> <want their outputs>
// The side is the caller's: our input wants somebody's output, our output wants somebody's
// input, and the device knows which because it picked one of our ports first.
// response: same shape as CMD_BUILDER_CONNECTION_LIST, so the HMI reads it with the
//           same parser: `r 1 <count> [<i|o> <other node id> <type bitmask> <label>] * count`
//           `i` is a box that could feed this one, `o` one this one could feed
//HMI action: fills the target list of "New connection..."
//HOST action: -
#define CMD_BUILDER_CONNECTION_TARGETS        "bcnt %i %i %i"

// builder ports of one box <node id> <bitmask> <side: 0 inputs, 1 outputs, 2 both>
// Both puts the inputs first, and the direction letter of each entry says which side
// it came from -- that is how the device learns which way the cable will run.
// response: same shape as CMD_BUILDER_CONNECTION_LIST, so the HMI reads it with the same
//           parser: `r 1 <count> [<i|o> <port index> <type bitmask> <label>] * count`
//           the index is the position in this very list, and is what CMD_BUILDER_CONNECTION_ADD
//           takes back
//HMI action: fills the port list, once a target box has been picked
//HOST action: -
#define CMD_BUILDER_CONNECTION_PORTS        "bcnp %i %i %i"

// builder wire one port to another
// <from node id> <from port index> <to node id> <to port index> <signal type bitmask>
// A port index of -1 leaves that end to the host, which takes the least used port of the
// right type -- so wiring a stereo box twice fills its two sides rather than doubling one.
// response: `r 1 <number of cables made>`
//HMI action: -
//HOST action: connects the ports and tells the web UI
#define CMD_BUILDER_CONNECTION_ADD        "bcna %i %i %i %i %i"


// builder plugin categories <signal type bitmask, 0 for all>
// Favourites and All come first, then the LV2 categories; an empty one is left out.
// response: `r 1 <count> [<index> <label>] * count`
//HMI action: fills the left column of the Add screen
//HOST action: -
#define CMD_BUILDER_CATALOG_CATEGORIES        "bcac %i"

// builder plugins of one category <category index> <signal type bitmask> <first wanted>
// The category index is the position in the list CMD_BUILDER_CATALOG_CATEGORIES just sent.
// A category can hold hundreds of plugins and the HMI has room for a few dozen, so it asks
// for a window and slides it as the user scrolls.
// response: `r 1 <total> <first> <count> [<index> <label>] * count`, indexes absolute
//HMI action: fills the right column of the Add screen
//HOST action: -
#define CMD_BUILDER_CATALOG_LIST        "bcal %i %i %i"

// builder add a plugin to the pedalboard <category index> <plugin index> <signal type bitmask>
// Both indexes are positions in the lists just sent, so the device never carries a URI.
// response: `r 1 <node id of the new box>`, or `r 1 -1` when it could not be added
//HMI action: refetches the graph focused on the new box
//HOST action: instantiates the plugin and tells the web UI
#define CMD_BUILDER_PLUGIN_ADD        "bpla %i %i %i %i"


// builder first letters of a category <category index> <signal type bitmask>
// Holding the plugin encoder down scrubs by letter instead of by row, which turns a list
// of hundreds into one of twenty-odd. The index is where that letter starts, absolute,
// the same numbering CMD_BUILDER_CATALOG_LIST uses.
// response: `r 1 <count> [<index> <letter>] * count`
//HMI action: fills the scrub overlay
//HOST action: -
#define CMD_BUILDER_CATALOG_INITIALS        "bcan %i %i"

// builder plugin info <category index> <plugin index> <signal type bitmask>
// The two positions are the ones CMD_BUILDER_PLUGIN_ADD would add, so the overlay is about
// the row under the cursor without the HMI having to name it. The description arrives one
// word to a token: a word holds no space, so nothing has to be escaped and the HMI wraps
// it to whatever width the panel has left.
// response: `r 1 <name> <brand> <category> <audio in> <audio out> <midi in> <midi out>
//            <cv in> <cv out> <word count> [<word>] * word count`, or `r 1 -1`
//HMI action: opens the info overlay
//HOST action: -
#define CMD_BUILDER_CATALOG_INFO        "bcai %i %i %i"

// builder remove plugin <node id>
// Takes the box off the board with every cable on it. Only a plugin: the capture and
// playback boxes are part of the picture and not part of the pedalboard.
// response: `r 1 1` when it is gone, `r 1 0` when it is not
//HMI action: refetches the graph around a neighbour
//HOST action: removes the instance and tells the web UI
#define CMD_BUILDER_PLUGIN_DELETE        "bpld %i"

// builder toggle a plugin <node id>
// Turns the box on the board off, or back on. The answer is the state it lands in, so the
// HMI can redraw its own picture without asking for the graph again -- and it is sent
// before the change is made, because a bypass the HMI is addressed to sends it commands of
// its own and it is spinning on this reply while it waits.
// response: `r 1 <1 bypassed, 0 not>`, or `r 1 -1` when there is no such plugin
//HMI action: redraws the box, dashed when bypassed
//HOST action: bypasses the plugin and tells the web UI
#define CMD_BUILDER_PLUGIN_BYPASS        "bplb %i"

// builder watch the board <1 on, 0 off>
// The HMI says when it is looking at the graph, so the host only watches the board while
// somebody is there to be told. Sent on entering the builder and again on leaving it, and
// leaving is also what a pedalboard load causes -- so a load never notifies.
// On enabling, the host takes note of the board as it stands and says nothing: the HMI has
// just fetched it.
// response: `r 0`
//HMI action: -
//HOST action: starts or stops watching the board for changes
#define CMD_BUILDER_PLUGIN_NOTIFY        "bpln %i"

// builder the board has changed
// Host to HMI, the only one in this family that goes that way. Sent when the board changed
// under the HMI -- edited from the web UI, most of the time -- while the watch above is on.
// Carries nothing: several of them collapse into one refetch anyway.
// response: `r 0`
//HMI action: refetches the graph, outside the callback, when it is next idle
//HOST action: -
#define CMD_BUILDER_PLUGIN_UPDATED        "bplu"

// builder actuators
// Every slot on the panel: each knob once per sub-page it turns over in, then the
// footswitches, which do not turn over. Which actuator and which sub-page a position is,
// is the host's business -- the HMI picks a row and hands the row back.
// response: `r 1 <count> [<label>] * count`
//HMI action: fills the second column
//HOST action: -
#define CMD_BUILDER_BINDING_ACTUATORS        "bbnal"

// builder bindable parameters <node id> <first> <count>
// The control ports of one box, bypass first. Windowed like the plugin catalogue, so the
// total comes back with the slice and the HMI slides it as the cursor walks.
// response: `r 1 <total> <first> <count> [<label>] * count`
//HMI action: fills the first column
//HOST action: -
#define CMD_BUILDER_BINDING_PARAMS        "bbnp %i %i %i"

// builder bindings on a page <page>
// Which slots already carry an addressing on that page, so the HMI can mark them and
// offer DEL. A page and a row of the actuator list together are one slot, and a slot
// holds one addressing.
// response: `r 1 <count> [<actuator index> <label>] * count`
//HMI action: marks the second column
//HOST action: -
#define CMD_BUILDER_BINDING_LIST        "bbnl %i"

// builder bind <node id> <parameter index> <page> <actuator index>
// The host answers BEFORE it starts, and that ordering matters: making an addressing sends
// the HMI commands of its own -- control_add, and set_available_pages -- each waiting for
// the HMI to answer, while the HMI is spinning on this reply and answers nothing. The link
// is a queue, so the reply has to go into it first. The answer therefore cannot say whether
// it worked; the HMI marks the slot it just filled and finds out at the next read if not.
// The second number is the slot the parameter came off: it holds one addressing, so
// binding it somewhere else takes it off wherever it was, and the mark there goes with it.
// -1 when it was on nothing, or on another page, which the HMI reads afresh when it goes
// there.
// response: `r 1 <1 accepted, 0 no such slot or parameter> <freed slot index, or -1>`
//HMI action: marks the slot in the second column and clears the freed one
//HOST action: addresses the parameter and tells the web UI and the panel
#define CMD_BUILDER_BINDING_ADD        "bbna %i %i %i %i"

// builder unbind <page> <actuator index>
// Answers before it starts, for the same reason bind does.
// response: `r 1 1` accepted, `r 1 0` when the slot holds nothing
//HMI action: clears the slot in the second column
//HOST action: unaddresses whatever held the slot and tells the web UI and the panel
#define CMD_BUILDER_BINDING_DELETE        "bbnd %i %i"


/*
********************************
    Selftest Specific commands
********************************
*/

//send if an encoder is clicked (used in selftest) <encoder_id>
//response: -
//HMI action: -
//HOST action: -
#define CMD_SELFTEST_ENCODER_CLICKED      "enc_clicked %i"

//send if an encoder is turned left (used in selftest) <encoder_id>
//response: -
//HMI action: -
//HOST action: -
#define CMD_SELFTEST_ENCODER_LEFT         "enc_left %i"

//send if an encoder is turned right (used in selftest) <encoder_id>
//response: -
//HMI action: -
//HOST action: -
#define CMD_SELFTEST_ENCODER_RIGHT        "enc_right %i"

//send if an button is clicked (used in selftest) <button_id>
//response: -
//HMI action: -
//HOST action: -
#define CMD_SELFTEST_BUTTON_CLICKED       "button_clicked %i"

//send so HMI can check calibration (used in selftest) <pot_id>
//response: -
//HMI action: check call and return id when ok
//HOST action: -
#define CMD_SELFTEST_CHECK_CALIBRATION    "pot_call_check %i"

//send if an button is clicked (used in selftest) <pot_id>
//response: -
//HMI action: -
//HOST action: -
#define CMD_SELFTEST_CALLIBRATION_OK      "pot_call_ok %i"

//send if the selftest hangs on a control to continue
//response: -
//HMI action: -
//HOST action: -
#define CMD_SELFTEST_SKIP_CONTROL_ENABLE  "control_skip_enable"

//send if the selftest hangs on a control to continue
//response: -
//HMI action: -
//HOST action: -
#define CMD_SELFTEST_SKIP_CONTROL         "control_bad_skip"

//send to the HMI to save the current value of a pot as the calibration value (used in selftest) <min/max> <pot_id>
//response: -
//HMI action: save current pot value as min/max calibration value
//HOST action: -
#define CMD_SELFTEST_SAVE_POT_CALIBRATION "save_pot_cal %i %i"

/*
********************************
    System commands (used on another serial bus)
********************************
*/

// All system commands must have "sys_" prefix
#define _CMD_SYS_PREFIX "sys_"

// All system commands must have length 7 (e,g. "sys_ver")
#define _CMD_SYS_LENGTH 7

// If system command has data, we specify how big it is in 2 digits in hexadecimal notation (e.g. "0c")
#define _CMD_SYS_DATA_LENGTH 2

//send I/O gain values to change <size arguments> <0 = in, 1 = out> <channel 1, 2 or 0 for both> <value>
//response: -
//HMI action: -
//HOST action: changes the gain in alsamixer
#define CMD_SYS_GAIN                    "sys_gio %02x %i %i %f"

//send HP gain value
//response: -
//HMI action: -
//HOST action: changes the gain in alsamixer <size arguments> <value>
#define CMD_SYS_HP_GAIN                 "sys_ghp %02x %f"

//send CV input mode
//response: -
//HMI action: -
//HOST action: changes the CV input mode in alsamixer <size arguments> <value>
#define CMD_SYS_CVI_MODE                "sys_cvi %02x %i"

//send expression port mode
//response: -
//HMI action: -
//HOST action: changes the expression input mode in alsamixer <size arguments> <value>
#define CMD_SYS_EXP_MODE                "sys_exp %02x %i"

//send CV output mode
//response: -
//HMI action: -
//HOST action: changes the CV output mode in alsamixer <size arguments> <value>
#define CMD_SYS_CVO_MODE               "sys_cvo %02x %i"

//send noisegate channel value
//response: if no argument for channel is givin, the current channel is returned
//HMI action: -
//HOST action: changes the noisegate channel <size arguments> <value>
#define CMD_SYS_NG_CHANNEL              "sys_ngc %02x %i"

//send noisegate threshold value
//response: if no argument for channel is givin, the current threshold is returned
//HMI action: -
//HOST action: changes the noisegate threshold <size arguments> <value>
#define CMD_SYS_NG_THRESHOLD            "sys_ngt %02x %i"

//send noisegate decay value
//response: if no argument for channel is givin, the current decay is returned
//HMI action: -
//HOST action: changes the noisegate decay <size arguments> <value>
#define CMD_SYS_NG_DECAY                "sys_ngd %02x %i"

//send compressor mode value
//response: if no argument for channel is givin, the current mode is returned
//HMI action: -
//HOST action: changes the compressor mode <size arguments> <value>
#define CMD_SYS_COMP_MODE                "sys_cmm %02x %i"

//send compressor release value
//response: if no argument for channel is givin, the current release is returned
//HMI action: -
//HOST action: changes the compressor release <size arguments> <value>
#define CMD_SYS_COMP_RELEASE             "sys_cmr %02x %i"

//send compressor pedalboard gain value
//response: if no argument for channel is givin, the current gain is returned
//HMI action: -
//HOST action: changes the pedalboard gain in the compressor <size arguments> <value>
#define CMD_SYS_COMP_PEDALBOARD_GAIN      "sys_pbg %02x %i"

//save mixer values
//response: -
//HMI action: -
//HOST action: saves the current alsamixer values to disk
#define CMD_SYS_AMIXER_SAVE              "sys_ams"

//request bluetooth status parameters from host
//response: bluetooth status parameters
//HMI action: -
//HOST action: replies with bluetooth status parameters
#define CMD_SYS_BT_STATUS                "sys_bts"

//enable bluetooth discovery
//response: -
//HMI action: -
//HOST action: enables bluetooth discovery
#define CMD_SYS_BT_DISCOVERY             "sys_btd"

//check status of systemctl services <size arguments> <name of service>
//response: status of service
//HMI action: -
//HOST action: reply status of service
#define CMD_SYS_SYSTEMCTL               "sys_ctl %02x %s"

//check current versions of sys components <size arguments> <name of component>
//response: version of component
//HMI action: -
//HOST action: reply version of component
#define CMD_SYS_VERSION                 "sys_ver %02x %s"

//check the device serial number
//response: serial number of device
//HMI action: -
//HOST action: serial number of device
#define CMD_SYS_SERIAL                   "sys_ser"

//change usb mode for next (re)boot
//response: -
//HMI action: -
//HOST action: current usb mode
#define CMD_SYS_USB_MODE                 "sys_usb %02x %i"

//toggle mod noise removal
//response: -
//HMI action: -
//HOST action: current noise removal mode
#define CMD_SYS_NOISE_REMOVAL            "sys_mnr %02x %i"

//reboot the system
//HMI action: -
//HOST action: calls "hmi-reset" and then "reboot"
#define CMD_SYS_REBOOT                   "sys_rbt"

// led set blink <assignment_id> <color_id> <on_time_ms> <off_time_ms>
//response: `r 0`
//HMI action: change assigned led color (-1 for a reset)
//HOST action: -
#define CMD_SYS_CHANGE_LED_BLINK         "sys_lbl %02x %i %i %i %i"

// led set brightness <assignment_id> <color_id> <brightness>
//response: `r 0`
//HMI action: change assigned led color (-1 for a reset)
//HOST action: -
#define CMD_SYS_CHANGE_LED_BRIGHTNESS     "sys_lbh %02x %i %i %i"

// name set <assignment_id> <new txt string>
//response: `r 0`
//HMI action: change assigned name txt
//HOST action: -
#define CMD_SYS_CHANGE_NAME              "sys_nam %02x %i %s"

// unit set <assignment_id> <new txt string>
//response: `r 0`
//HMI action: change assigned unit txt
//HOST action: -
#define CMD_SYS_CHANGE_UNIT              "sys_uni %02x %i %s"

// name set <assignment_id> <new txt string>
//response: `r 0`
//HMI action: change assigned name txt
//HOST action: -
#define CMD_SYS_CHANGE_VALUE              "sys_val %02x %i %s"

// unit set <assignment_id> <indicator val 0.0 to 1.0>
//response: `r 0`
//HMI action: change assigned unit txt
//HOST action: -
#define CMD_SYS_CHANGE_WIDGET_INDICATOR   "sys_ind %02x %i %f"

// unit set <assignment_id> <style_id> <header text> <popup text>
//response: `r 0`
//HMI action: launches a temporary popup with plugin info
//HOST action: -
#define CMD_SYS_LAUNCH_POPUP              "sys_pop %02x %i %i %s %s"

// notifies the system the user changed a page <new_page_id>
//response: `r 0`
//HMI action: -
//HOST action: -
#define CMD_SYS_PAGE_CHANGE              "sys_pch %02x %i"

// notifies the system the user changed a subpage <new_subpage_id>
//response: `r 0`
//HMI action: -
//HOST action: -
#define CMD_SYS_SUBPAGE_CHANGE          "sys_spc %02x %i"

/*
********************************
    Command count per device
********************************
*/

#define COMMAND_COUNT_DUO   118
#define COMMAND_COUNT_DUOX  120
#define COMMAND_COUNT_DWARF 115

/*
********************************
    Banks functions definitions
********************************
*/

#define BANK_FUNC_NONE                  0
#define BANK_FUNC_TRUE_BYPASS           1
#define BANK_FUNC_PEDALBOARD_NEXT       2
#define BANK_FUNC_PEDALBOARD_PREV       3
#define BANK_FUNC_COUNT                 4

/*
********************************
    Flags/bitmasks definitions
********************************
*/

//bank and pedlboard navigation bitmasks
#define FLAG_NAVIGATION_FACTORY         0x1
#define FLAG_NAVIGATION_READ_ONLY       0x2
#define FLAG_NAVIGATION_DIVIDER         0x4
#define FLAG_NAVIGATION_TRIAL_PLUGINS   0x8

//command bitmask definitions
#define FLAG_CONTROL_BYPASS             0x001
#define FLAG_CONTROL_TAP_TEMPO          0x002
#define FLAG_CONTROL_ENUMERATION        0x004
#define FLAG_CONTROL_SCALE_POINTS       0x008
#define FLAG_CONTROL_TRIGGER            0x010
#define FLAG_CONTROL_TOGGLED            0x020
#define FLAG_CONTROL_LOGARITHMIC        0x040
#define FLAG_CONTROL_INTEGER            0x080
#define FLAG_CONTROL_REVERSE            0x100
#define FLAG_CONTROL_MOMENTARY          0x200

//list pagination bitmasks
#define FLAG_PAGINATION_PAGE_UP         0x1
#define FLAG_PAGINATION_WRAP_AROUND     0x2
#define FLAG_PAGINATION_INITIAL_REQ     0x4
#define FLAG_PAGINATION_ALT_LED_COLOR   0x8

//scalepoints bitmasks
#define FLAG_SCALEPOINT_PAGINATED       0x1
#define FLAG_SCALEPOINT_WRAP_AROUND     0x2
#define FLAG_SCALEPOINT_END_PAGE        0x4
#define FLAG_SCALEPOINT_ALT_LED_COLOR   0x8

/*
********************************
    Menu Item ID's
********************************
Each menu item in the MOD OS has its own ID, this allows for it to be easily changed and parsed to both sides of the system
*/

//shared
#define MENU_ID_SL_IN                   0
#define MENU_ID_SL_OUT                  1
#define MENU_ID_TUNER_MUTE              2
#define MENU_ID_QUICK_BYPASS            3
#define MENU_ID_PLAY_STATUS             4
#define MENU_ID_MIDI_CLK_SOURCE         5
#define MENU_ID_MIDI_CLK_SEND           6
#define MENU_ID_SNAPSHOT_PRGCHGE        7
#define MENU_ID_PB_PRGCHNGE             8
#define MENU_ID_TEMPO                   9
#define MENU_ID_BEATS_PER_BAR           10
#define MENU_ID_BYPASS1                 11
#define MENU_ID_BYPASS2                 12
#define MENU_ID_BRIGHTNESS              13
#define MENU_ID_CURRENT_PROFILE         14
//duo
#define MENU_ID_FOOTSWITCH_NAV          30
//duox
#define MENU_ID_EXP_CV_INPUT            40
#define MENU_ID_HP_CV_OUTPUT            41
#define MENU_ID_MASTER_VOL_PORT         42
#define MENU_ID_EXP_MODE                43
//dwarf

#define MENU_ID_TOP                     44

/*
********************************
    Response error messages
********************************
*/

// error messages configuration
#define RESP_ERR_COMMAND_NOT_FOUND      "not found"
#define RESP_ERR_MANY_ARGUMENTS         "many arguments"
#define RESP_ERR_FEW_ARGUMENTS          "few arguments"
#define RESP_ERR_INVALID_ARGUMENT       "invalid argument"
