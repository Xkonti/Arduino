/*

 

 */

#ifndef __TFT_GUI_H__
#define __TFT_GUI_H__

#include <Arduino.h>
#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9340.h"

#if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
#endif

/*
#define	BTN_TEXT		0x0000
#define	BTN_FILL		0xAAAA
#define	BTN_FILLS		0xCCCC
#define	BTN_BORDER		0x3333
#define	BTN_BORDERS		0xFFFF

#define	MENU_BG			0x0000
#define	MENU_TEXT		0xFFFF

#define	GRAPH_BG		0x0000
#define	GRAPH_GRID		0x2222
#define	GRAPH_LEGEND	0x2222
#define	GRAPH_DATA1		0x2222
#define	GRAPH_DATA2		0x2222
#define	GRAPH_DATA3		0x2222
*/
class TFT_GUI : public Adafruit_ILI9340 {

public:
	// COLORS
	uint16_t BTN_TEXT;
	uint16_t BTN_FILL;
	uint16_t BTN_FILLS;
	uint16_t BTN_BORDER;
	uint16_t BTN_BORDERS;
	
	uint16_t MENU_BG;
	uint16_t MENU_TEXT;
	
	uint16_t GRAPH_BG;
	uint16_t GRAPH_BORDER;
	uint16_t GRAPH_GRID;
	uint16_t GRAPH_LEGEND;
	uint16_t GRAPH_DATA1;
	uint16_t GRAPH_DATA2;
	uint16_t GRAPH_DATA3;
	
	uint16_t ERROR_BG;
	uint16_t ERROR_TEXT;
	uint16_t MSG_BG;
	uint16_t MSG_TEXT;



	int pinUp;
	int pinDown;
	int pinFeedback;

	TFT_GUI(uint8_t CS, uint8_t RS, uint8_t MOSI, uint8_t SCLK, uint8_t RST, uint8_t MISO);
	TFT_GUI(uint8_t CS, uint8_t RS, uint8_t RST);

	void setup(int _pinUp, int _pinDown, int _pinFeedback);
	void drawError(String _description);
	void drawMessage(String _title, String _description);
	void drawButton(int _y, String _text, bool _selected);
	void drawGraph(int* data, int x, int y, int w, int h, int min, int max, bool grid, bool legend);
	
	int getPress(int pin);
	int getPress(int pin, int _feedback);
	int getPress(int pin, int _shortFeedback, int _longFeedback);
	int getPress(int pin, int _shortFeedback, int _mediumFeedback, int _longFeedback);
	int getTimedPress(int pin, int interval);
	int getTimedPress(int pin, int shorterInterval, int longerInterval);
	int getTimedPress(int pin, int shorterInterval, int mediumInterval, int longerInterval);
	void getOk(int _okPin);
	
	void feedback(int _time);
	
private:
	
};


/*
class TFT_Button {
public:
	int x, y;
	String text;
	bool selected;
	
	TFT_Button(TFT_GUI* _gui, int _y, String _text, bool _selected);
	void draw();
private:
	TFT_GUI* gui;
};
*/

class TFT_Menu {
public:
	String text;

	TFT_Menu(TFT_GUI* _gui, String _text);
	int add(String _text, bool _redraw);
	void add(String _text, int _index, bool _redraw);
	void remove(bool _redraw);
	void remove(int _index, bool _redraw);
	void rename(int _index, String newName, bool _redraw);
	int length();
	void select(int _index, bool _redraw);
	void selectUp(bool _redraw);
	void selectDown(bool _redraw);
	void draw();
	void redraw();
	void redraw(int first, int second);
	void reset(bool _redraw);
	
	int interact();
	void edit();
private:
	TFT_GUI* gui;
	String buttons[13];
	int len;
	int selected;
	
	void rearrange();
};

class TFT_Graph {
public:
	int x;
	int y;
	int width;
	int height;
	
	int min;
	int max;
	float verticalZoom;
	float horizontalZoom;
	
	bool showGrid;
	bool showLegend;
	bool autoZoom;
	
	TFT_Graph(TFT_GUI* gui, int _dataLength, int _x, int _y, int _width, int _height, bool _showGrid, bool _showLegend);
	TFT_Graph(TFT_GUI* gui, int _dataLength, int _x, int _y, int _width, int _height, int _min, int _max, bool _showGrid, bool _showLegend);
	
	void draw();
	
	void push(int value);
	
private:
	TFT_GUI* gui;

	int* data;
	int len;
	
	
	void calculateVZoom(bool multipilerOnly);
	void calculateHZoom();
	
	void drawBase();
	void drawGrid();
	void drawLegend();
	void drawData();
};

#endif
