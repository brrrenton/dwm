/*
In monocle layout (assuming monocle layout is the last layout) call focusstack
In any other layout call zoom
*/
void
combokey(const Arg *arg) {
    if (selmon->lt[selmon->sellt] == &layouts[LENGTH(layouts) - 2]){
        focusstack(arg);
    }
    else {
        zoom(0);
    }
}

