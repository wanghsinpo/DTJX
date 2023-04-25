const St      = imports.gi.St;
const Main    = imports.ui.main;
const Gio     = imports.gi.Gio;
const Util    = imports.misc.util;

let startButton, stopButton;
let startIcon = Gio.icon_new_for_string("/opt/SPECS_FA/sys/resource/icons/startfa.pm");
let stopIcon = Gio.icon_new_for_string("/opt/SPECS_FA/sys/resource/icons/stopfa.pm");

function _startFA() {
    Util.spawn(['/opt/SPECS_FA/sys/bin/startfa_shell']); 
}

function _stopFA() {
    Util.spawn(['/opt/SPECS_FA/sys/bin/stopfa_shell']); 
}

function init() {
    let startfa = Gio.File.new_for_path('/opt/SPECS_FA/sys/bin/startfa_shell');
    if (!startfa.query_exists(null)) {
        return;
    }
    let stopfa = Gio.File.new_for_path('/opt/SPECS_FA/sys/bin/stopfa_shell');
    if (!stopfa.query_exists(null)) {
        return;
    }
    startButton = new St.Bin({ style_class: 'panel-button',
                          reactive: true,
                          can_focus: true,
                          x_fill: true,
                          y_fill: false,
                          track_hover: true });
    let start_icon = new St.Icon({icon_size: 25,  gicon : startIcon});
    startButton.set_child(start_icon);
    startButton.connect('button-press-event', _startFA);

    stopButton = new St.Bin({ style_class: 'panel-button',
                          reactive: true,
                          can_focus: true,
                          x_fill: true,
                          y_fill: false,
                          track_hover: true });
    let stop_icon = new St.Icon({icon_size: 25,  gicon : stopIcon});
    stopButton.set_child(stop_icon);
    stopButton.connect('button-press-event', _stopFA);
}

function enable() {
    if (stopButton != null && startButton != null) {
        Main.panel._rightBox.insert_child_at_index(stopButton, 0);
        Main.panel._rightBox.insert_child_at_index(startButton, 0);
    }
}

function disable() {
    if (stopButton != null && startButton != null) {
        Main.panel._rightBox.remove_child(startButton);
        Main.panel._rightBox.remove_child(stopButton);
    }
}
