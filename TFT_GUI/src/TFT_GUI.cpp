/*
*/

#include "TFT_GUI.h"

TFT_GUI::TFT_GUI(uint8_t CS, uint8_t RS, uint8_t MOSI, uint8_t SCLK, uint8_t RST, uint8_t MISO) : Adafruit_ILI9340(CS, RS, MOSI, SCLK, RST, MISO) {
	BTN_TEXT = Color565(0, 0, 0);
	BTN_FILL = Color565(192, 192, 192);
	BTN_FILLS = Color565(192, 192, 50);
	BTN_BORDER = Color565(64, 64, 64);
	BTN_BORDERS = Color565(255, 255, 255);
	
	MENU_BG = Color565(0, 0, 0);
	MENU_TEXT = Color565(255, 255, 255);
	
	GRAPH_BG = Color565(0, 0, 0);
	GRAPH_BORDER = Color565(128, 128, 128);
	GRAPH_GRID = Color565(64, 64, 64);
	GRAPH_LEGEND = Color565(128, 128, 32);
	GRAPH_DATA1 = Color565(200, 50, 50);
	GRAPH_DATA2 = Color565(50, 200, 50);
	GRAPH_DATA3 = Color565(50, 50, 200);
	
	ERROR_BG = Color565(255, 0, 0);
	ERROR_TEXT = Color565(255, 255, 255);
	MSG_BG = Color565(0, 0, 0);
	MSG_TEXT = Color565(200, 200, 255);
}

TFT_GUI::TFT_GUI(uint8_t CS, uint8_t DC, uint8_t RST) : Adafruit_ILI9340(CS, DC, RST) {
	BTN_TEXT = Color565(0, 0, 0);
	BTN_FILL = Color565(192, 192, 192);
	BTN_FILLS = Color565(192, 192, 50);
	BTN_BORDER = Color565(64, 64, 64);
	BTN_BORDERS = Color565(255, 255, 255);
	
	MENU_BG = Color565(0, 0, 0);
	MENU_TEXT = Color565(255, 255, 255);
	
	GRAPH_BG = Color565(0, 0, 0);
	GRAPH_BORDER = Color565(128, 128, 128);
	GRAPH_GRID = Color565(64, 64, 64);
	GRAPH_LEGEND = Color565(128, 128, 32);
	GRAPH_DATA1 = Color565(200, 50, 50);
	GRAPH_DATA2 = Color565(50, 200, 50);
	GRAPH_DATA3 = Color565(50, 50, 200);
	
	ERROR_BG = Color565(255, 0, 0);
	ERROR_TEXT = Color565(255, 255, 255);
	MSG_BG = Color565(0, 0, 0);
	MSG_TEXT = Color565(200, 200, 255);
}

void TFT_GUI::setup(int _pinUp, int _pinDown, int _pinFeedback) {
	begin();
	
	pinUp = _pinUp;
	pinDown = _pinDown;
	pinFeedback = _pinFeedback;
	pinMode(pinUp, INPUT);
	pinMode(pinDown, INPUT);
	pinMode(pinFeedback, OUTPUT);
	digitalWrite(pinFeedback, LOW);
}

void TFT_GUI::drawError(String _description) {
	fillScreen(ERROR_BG);
	setCursor(0,0);
	setTextColor(ERROR_TEXT);
	setTextSize(4);
	println("ERROR");
	setTextSize(2);
	println(_description);
	getOk(pinDown);
}

void TFT_GUI::drawMessage(String _title, String _description) {
	fillScreen(MSG_BG);
	setCursor(0,0);
	setTextColor(MSG_TEXT);
	setTextSize(3);
	println(_title);
	setTextSize(1);
	println(_description);
	getOk(pinDown);
}

void TFT_GUI::drawButton(int _y, String _text, bool _selected) {
	if (!_selected) {
		fillRect (1, _y + 1, width() - 2, 18, BTN_FILL);
		drawRect (0, _y, width(), 20, BTN_BORDER);
	}
	else {
		fillRect (1, _y + 1, width() - 2, 18, BTN_FILLS);
		drawRect (0, _y, width(), 20, BTN_BORDERS);
	}
	
	setCursor(2, _y + 2);
	setTextColor(BTN_TEXT);
	setTextSize(2);
	print(_text);
}

void TFT_GUI::drawGraph(int* data, int x, int y, int w, int h, int min, int max, bool grid, bool legend) {



}

int TFT_GUI::getPress(int pin) {
	bool pressed = digitalRead(pin);
	int temp = millis();
	int time = 0;
	if (pressed) {
		delay(10);
		if (digitalRead(pin)) {      
			delay(10);
			
			while (digitalRead(pin)) {
				delay(10);
			}
			time = millis() - temp;
		}
	}
	return time;
}

int TFT_GUI::getPress(int _pin, int _feedback) {
	bool feed = true;  
	bool pressed = digitalRead(_pin);
	int temp = millis();
	int time = 0;
	if (pressed) {
		delay(10);
		if (digitalRead(_pin)) {      
			delay(10);
			
			while (digitalRead(_pin)) {
				if (time >= _feedback && feed) { feedback(50); feed = false; }
				delay(10);
				time = millis() - temp;
			}
		}
	}
	return time;
}

int TFT_GUI::getPress(int _pin, int _shortFeedback, int _longFeedback) {
	bool sfeed = true;
	bool lfeed = true;
	bool pressed = digitalRead(_pin);
	int temp = millis();
	int time = 0;
	if (pressed) {
		delay(10);
		if (digitalRead(_pin)) {      
			delay(10);
			
			while (digitalRead(_pin)) {
				if (time >= _shortFeedback && sfeed) { feedback(50); sfeed = false; }
				else if (time >= _longFeedback && lfeed) { feedback(50); lfeed = false; }
				delay(10);
				time = millis() - temp;
			}
		}
	}
	return time;
}

int TFT_GUI::getPress(int _pin, int _shortFeedback, int _mediumFeedback, int _longFeedback) {
	bool sfeed = true;
	bool mfeed = true;
	bool lfeed = true;
	bool pressed = digitalRead(_pin);
	int temp = millis();
	int time = 0;
	if (pressed) {
		delay(10);
		if (digitalRead(_pin)) {      
			delay(10);
			
			while (digitalRead(_pin)) {
				if (time >= _shortFeedback && sfeed) { feedback(50); sfeed = false; }
				else if (time >= _mediumFeedback && mfeed) { feedback(50); mfeed = false; }
				else if (time >= _longFeedback && lfeed) { feedback(50); lfeed = false; }
				delay(10);
				time = millis() - temp;
			}
		}
	}
	return time;
}

int TFT_GUI::getTimedPress(int pin, int interval) {
	if (getPress(pin, interval) >= interval) return 1;
	else return 0;
}

int TFT_GUI::getTimedPress(int pin, int shorterInterval, int longerInterval) {
	int time = getPress(pin, shorterInterval, longerInterval);
	if (time >= longerInterval) return 2;
	else if (time >= shorterInterval) return 1;
	else return 0;
}

int TFT_GUI::getTimedPress(int pin, int shorterInterval, int mediumInterval, int longerInterval) {
	int time = getPress(pin, shorterInterval, mediumInterval, longerInterval);
	if (time >= longerInterval) return 3;
	else if (time >= mediumInterval) return 2;
	else if (time >= shorterInterval) return 1;
	else return 0;
}

void TFT_GUI::getOk(int _okPin) { while(true) { if (getPress(_okPin)) break; } }

void TFT_GUI::feedback(int _time) {
	digitalWrite(pinFeedback, HIGH);
	delay(_time);
	digitalWrite(pinFeedback, LOW);
}


//===================================================================================
//===================================================================================
/*

TFT_Button::TFT_Button(TFT_GUI* _gui, int _y, String _text, bool _selected) {
	gui = _gui;
	y = _y;
	text = _text;
	selected = _selected;
}

void TFT_Button::draw() {
	if (!selected) {
		gui->fillRect (1, y + 1, gui->width() - 2, 18, BTN_FILL);
		gui->drawRect (0, y, gui->width(), 20, BTN_BORDER);
	}
	else {
		gui->fillRect (1, y + 1, gui->width() - 2, 18, BTN_FILLS);
		gui->drawRect (0, y, gui->width(), 20, BTN_BORDERS);
	}
	
	gui->setCursor(2, y + 2);
	gui->setTextColor(BTN_TEXT);
	gui->setTextSize(2);
	gui->print(text);
}

*/
//===================================================================================
//===================================================================================


TFT_Menu::TFT_Menu(TFT_GUI* _gui, String _text) {

	gui = _gui;
	for (int i = 0; i < 13; i++) buttons[i] = "";
	text = _text;
	len = 0;
	selected = 0;

}

int TFT_Menu::add(String _text, bool _redraw) {
	if (len < 13) {
		buttons[len] = _text;
		len++;
		if (_redraw) redraw();
		return len-1;
	}
	else {
		gui->drawError("Can't add more buttons to " + text);
		draw();
		return 13;
	}
}

void TFT_Menu::add(String _text, int _index, bool _redraw) {
	if (len < 13) {
		if (_index > len) _index = len;
		if (_index < 13 && _index >= 0) {
			int i = len;
			while (i > _index) {
				buttons[i] = buttons[i - 1];
				i--;
			}
			buttons[_index] = _text;
			len++;
			if (_redraw) draw();
		} else { gui->drawError("Can't add button in position" + String(_index)); draw(); }
	}
	else { gui->drawError("Can't add more buttons to " + text); draw(); }
}

void TFT_Menu::remove(bool _redraw) { remove(selected, _redraw); }

void TFT_Menu::remove(int _index, bool _redraw) {
	if (len > 0) {
		if (_index < len) {
			buttons[_index] = "";
			rearrange();
			len--;
			if (_redraw) draw();
		}
		else { gui->drawError("Can't remove button with index over 12."); draw(); }
	} else { gui->drawError("There are no buttons to remove."); draw(); }
}

void TFT_Menu::rename(int _index, String newName, bool _redraw) {
	if (_index < len) {
		if (buttons[_index] != "") {
			buttons[_index] = newName;
			if (_redraw) redraw();
		}
		else { gui->drawError("Can't rename button that doesn't exist."); draw(); }
	}
	else { gui->drawError("Can't rename button with index over 12."); draw(); }
}

int TFT_Menu::length() { return len; }

void TFT_Menu::select(int _index, bool _redraw) {
	if (_index < len) {
		int old = selected;
		selected = _index;
		if (_redraw) redraw(old, _index);
	}
	
}

void TFT_Menu::selectUp(bool _redraw) {
	if (len > 0) {
		int old = selected;
		if (selected - 1 < 0) selected = len - 1;
		else selected -= 1;
		if (_redraw) { redraw(old, selected); }
	}
}

void TFT_Menu::selectDown(bool _redraw) {
	if (len > 0) {
		int old = selected;
		if (selected + 1 > len - 1) selected = 0;
		else selected += 1;
		if (_redraw) { redraw(old, selected); }
	}
}

void TFT_Menu::draw() {
	gui->fillScreen(gui->MENU_BG);
	redraw();
}

void TFT_Menu::redraw() {
	gui->setCursor(0, 0);
	gui->setTextColor(gui->MENU_TEXT);
	gui->setTextSize(2);
	gui->print(text);
	for (int i = 0; i < len; i++) {
		gui->drawButton(25 + i * 22, buttons[i], i == selected);
	}
}

void TFT_Menu::redraw(int first, int second) {
	gui->drawButton(25 + first * 22, buttons[first], first == selected);
	gui->drawButton(25 + second * 22, buttons[second], second == selected);
}

void TFT_Menu::reset(bool _redraw) {
	for (int i = 0; i < 13; i++) {
		buttons[i] = "";
	}
	selected = 0;
	if (_redraw) draw();
}

int TFT_Menu::interact() {
	
	if (len > 0) {
	
		gui->drawMessage("Choosing entry", "You can choose entry using two buttons:\nUP:\n - Short[30ms] - Move selection up\n - Long[600ms] - Cancel\nDOWN:\n - Short[30ms] - Move selection down\n - Long[600ms] - Accept selection");
			
		selected = 0;
		draw();
		while(true) {
			int btn = gui->getTimedPress(gui->pinUp, 30, 600);
			if (btn == 1) selectUp(true);
			else if (btn == 2) return 13;
			else {
				btn = gui->getTimedPress(gui->pinDown, 30, 600);
				if (btn == 1) selectDown(true);
				else if (btn == 2) return selected;
			}
		}
	} else {
		gui->drawError("There are no entries to choose from");
		return 13;
	}
}

void TFT_Menu::edit() {

	gui->drawMessage("Editing menu", "You can edit entries using two buttons:\nUP:\n - Short[30ms] - Move selection up\n - Medium[600ms] - Remove selected entry\n - Long[2000ms] - End editing menu\nDOWN:\n - Short[30ms] - Move selection down\n - Medium[600ms] - Add entry below selection\n - Long[2000ms] - Add entry above selection");
		
	selected = 0;
	draw();
	
	bool done = false;
	while(!done) {
		int btn = gui->getTimedPress(gui->pinUp, 30, 600, 2000);
		if (btn == 1) selectUp(true);
		else if (btn == 2) remove(true);
		else if (btn == 3) done = true;
		else {
			btn = gui->getTimedPress(gui->pinDown, 30, 600, 2000);
			if (btn == 1) selectDown(true);
			else if (btn == 2) add("Entry " + String(len+1), selected + 1, true);
			else if (btn == 3) add("Entry " + String(len+1), selected, true);
		}
	}
}

void TFT_Menu::rearrange() {
	int i = 0;
	while (i < 12) {
		if (buttons[i] == "") {
			for (int j = i + 1; j < 13; j++) {
				buttons[j-1] = buttons[j];
			}
			buttons[12] = "";
		}
		i++;
	}
	selected = 0;
}


//===================================================================================
//===================================================================================


TFT_Graph::TFT_Graph(TFT_GUI* _gui, int _dataLength, int _x, int _y, int _width, int _height, bool _showGrid, bool _showLegend) {
	gui = _gui;
	len = _dataLength;
	
	data = new int[len];
	for (int i = 0; i < len; i++) { data[i] = 0; }
	
	x = _x; y = _y;
	width = _width;
	height = _height;
	showGrid = _showGrid;
	showLegend = _showLegend;
	autoZoom = true;
	
	calculateVZoom(!autoZoom);
	calculateHZoom();
}

TFT_Graph::TFT_Graph(TFT_GUI* _gui, int _dataLength, int _x, int _y, int _width, int _height, int _min, int _max, bool _showGrid, bool _showLegend) {
	gui = _gui;
	len = _dataLength;
	
	data = new int[len];
	for (int i = 0; i < len; i++) { data[i] = 0; }
	
	x = _x; y = _y;
	width = _width;
	height = _height;
	min = _min; max = _max;
	showGrid = _showGrid;
	showLegend = _showLegend;
	autoZoom = false;
	calculateVZoom(!autoZoom);
	calculateHZoom();
}

void TFT_Graph::draw() {
	if (autoZoom) { calculateVZoom(!autoZoom); }
	
	drawBase();
	if (showGrid) { drawGrid(); }
	drawData();
	if (showLegend) { drawLegend(); }
}

void TFT_Graph::push(int value) {
	for (int i = 0; i < len - 1; i++) { data[i] = data[i+1]; }
	data[len-1] = value;
}


void TFT_Graph::calculateVZoom(bool multipilerOnly) {
	if (!multipilerOnly) {
		int _minMax = data[0];
		for (int i = 1; i < len; i++) { if (data[i] < _minMax) _minMax = data[i]; }
		min = _minMax;
		
		_minMax = data[0];
		for (int i = 1; i < len; i++) { if (data[i] > _minMax) _minMax = data[i]; }
		max = _minMax;
	}
	
	float _max = max;
	float _min = min;
	float h = height - 2;
	float range = _max - _min + 2;
	verticalZoom = h / range;
}

void TFT_Graph::calculateHZoom() {
	float w = width - 2;
	float l = len;
	horizontalZoom = w / l;
}

void TFT_Graph::drawBase() {
	gui->fillRect (x + 1, y + 1, width - 2, height - 2, gui->GRAPH_BG);
	gui->drawRect (x, y, width, height, gui->GRAPH_BORDER);
}

void TFT_Graph::drawGrid() {
	if (len > 4 && (width - 2) / 2 > len) {
		for(int i = 1; i < len / 4; i++) { gui->drawFastVLine(x + 1 + (4 * i * horizontalZoom), y + 1, height - 2, gui->GRAPH_GRID); }
	}
}

void TFT_Graph::drawLegend() {

}

void TFT_Graph::drawData() {
	for (int i = 0; i < len - 1; i++) {
		float x1 = x + 1 + (i * horizontalZoom);
		float y1 = y + 1 + ((max - data[i] + 1) * verticalZoom);
		float x2 = x + 1 + ((i + 1) * horizontalZoom);
		float y2 = y + 1 + ((max - data[(i + 1)] + 1) * verticalZoom);
		gui->drawLine(x1, y1, x2, y2, gui->GRAPH_DATA1);
	}
}