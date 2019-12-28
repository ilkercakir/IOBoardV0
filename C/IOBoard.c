#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include <locale.h>

#include "iochannels.h"

// compile with gcc -std=c99 -Wall -c "%f" -DIS_RPI -DSTANDALONE -D__STDC_CONSTANT_MACROS -D__STDC_LIMIT_MACROS -DTARGET_POSIX -D_LINUX -fPIC -DPIC -D_REENTRANT -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -U_FORTIFY_SOURCE -g -ftree-vectorize -pipe -DUSE_VCHIQ_ARM -Wno-psabi -mcpu=cortex-a53 -mfloat-abi=hard -mfpu=neon-fp-armv8 -mneon-for-64bits $(pkg-config --cflags gtk+-3.0) -Wno-deprecated-declarations
// link with gcc -std=c99 -Wall -o "%e" "%f" $(pkg-config --cflags gtk+-3.0) -Wl,--whole-archive -lrt -ldl -lm -Wl,--no-whole-archive -rdynamic $(pkg-config --libs gtk+-3.0) -lwiringPi

typedef struct
{
	GtkWidget *frame;
	GtkWidget *hbox;
	GtkWidget *label;
	GtkWidget *control;
}devicewidgets;

typedef struct
{
	GtkWidget *window;
	GtkWidget *container;
	devicewidgets dw[12];
}controlpanel;

gboolean widget_state_set(GtkWidget *togglebutton, gboolean state, gpointer data)
{
	actuator *a = (actuator*)data;

	ochannel_set_value(a->parent, a->channel, (state?0x01:0x00));
	ochannel_write(a->parent);

//printf("channel %d value %c\n", a->channel, (ochannel_get_value(a->parent, a->channel)?'1':'0'));

	return(TRUE);
}

void combo_changed(GtkWidget *combo, gpointer data)
{
	actuator *a = (actuator*)data;
	gchar *strval;

	g_object_get((gpointer)combo, "active-id", &strval, NULL);
	//printf("Selected id %s\n", strval);
	a->value = atoi((const char *)strval);
	g_free(strval);

	ochannel_write(a->parent);

//printf("channel %d value %c\n", a->channel, ochannel_get_value(a->parent, a->channel) + '0');
}

gboolean widget_state_set_bit(GtkWidget *togglebutton, gboolean state, gpointer data)
{
	actuator *a = (actuator*)data;
	switch_values value = (state?SWITCH_ON:SWITCH_OFF);

	obit_set_value(a->parent, a->channel, value);

//printf("bit %d value %c\n", a->channel, (obit_get_value(a->parent, a->channel)?'1':'0'));

	return(TRUE);
}

static void button_clicked_pulse(GtkWidget *button, gpointer data)
{
	actuator *a = (actuator*)data;

	opulse_out(a->parent, a->channel, 1000000);
}

void add_channelframe(controlpanel *cp, controller *c, int channel)
{
// frame
	cp->dw[channel].frame = gtk_frame_new(c->actuators[channel].name);
	//gtk_container_add(GTK_CONTAINER(ae->container), ae->frame);
	gtk_box_pack_start(GTK_BOX(cp->container), cp->dw[channel].frame, TRUE, TRUE, 0);

// horizontal box
	cp->dw[channel].hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_container_add(GTK_CONTAINER(cp->dw[channel].frame), cp->dw[channel].hbox);
	//gtk_box_pack_start(GTK_BOX(ae->frame), ae->hbox, TRUE, TRUE, 0);

	GtkWidget *w;

	cp->dw[channel].label = gtk_label_new(c->actuators[channel].name);
	//gtk_widget_set_size_request(cp->dw[channel].label, 100, 30);
	gtk_container_add(GTK_CONTAINER(cp->dw[channel].hbox), cp->dw[channel].label);

	switch (c->actuators[channel].type)
	{
		case A_LEVEL:
			cp->dw[channel].control = w = gtk_combo_box_text_new();

			int i;
			char s[10];
			for(i=0;i<c->actuators[channel].numstates;i++)
			{
				sprintf(s, "%d", i);
				//printf("val = %s\n", s);
				gchar *gc = g_strnfill(10, '\0');
				g_stpcpy(gc, (const char *)s);
				gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(w), gc, gc);
				g_free(gc);
			}
			sprintf(s, "%d", c->actuators[channel].value);
			g_object_set((gpointer)w, "active-id", s, NULL);
			g_signal_connect(GTK_COMBO_BOX(w), "changed", G_CALLBACK(combo_changed), &(c->actuators[channel]));
			gtk_container_add(GTK_CONTAINER(cp->dw[channel].hbox), w);
			//gtk_box_pack_start(GTK_BOX(ae->parameter[i].vbox), w, TRUE, TRUE, 0);
			break;
		case A_SWITCH:
		case A_PULSE:
		default:
			cp->dw[channel].control = w = gtk_switch_new();
			gtk_switch_set_active(GTK_SWITCH(w), c->actuators[channel].value);
			g_signal_connect(GTK_SWITCH(w), "state-set", G_CALLBACK(widget_state_set), &(c->actuators[channel]));
			gtk_container_add(GTK_CONTAINER(cp->dw[channel].hbox), w);
			//gtk_box_pack_start(GTK_BOX(cp->dw[channel].hbox), w, TRUE, TRUE, 0);
			break;
	}
}

int add_channeldevice(controlpanel *cp, controller *c, char *name, actuator_type type, int nstates)
{
	int i;

	switch (i = ochannel_add(c, name, type, nstates))
	{
		case CONTROLLER_INVALID_STATES:
			printf("ochannel_add() err=%d\n", i);
			break;
		case CONTROLLER_INVALID_ACTUATOR:
			printf("ochannel_add() err=%d\n", i);
			break;
		case CONTROLLER_FULL:
			printf("ochannel_add() err=%d\n", i);
			break;
		default:
			add_channelframe(cp, c, i);
	}

	return(i);
}

void add_bitframe(controlpanel *cp, controller *c, int channel)
{
// frame
	cp->dw[channel].frame = gtk_frame_new(c->actuators[channel].name);
	//gtk_container_add(GTK_CONTAINER(ae->container), ae->frame);
	gtk_box_pack_start(GTK_BOX(cp->container), cp->dw[channel].frame, TRUE, TRUE, 0);

// horizontal box
	cp->dw[channel].hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_container_add(GTK_CONTAINER(cp->dw[channel].frame), cp->dw[channel].hbox);
	//gtk_box_pack_start(GTK_BOX(ae->frame), ae->hbox, TRUE, TRUE, 0);

	GtkWidget *w;

	cp->dw[channel].label = gtk_label_new(c->actuators[channel].name);
	//gtk_widget_set_size_request(cp->dw[channel].label, 100, 30);
	gtk_container_add(GTK_CONTAINER(cp->dw[channel].hbox), cp->dw[channel].label);

	cp->dw[channel].control = w = gtk_switch_new();
	gtk_switch_set_active(GTK_SWITCH(w), c->actuators[channel].value);
	g_signal_connect(GTK_SWITCH(w), "state-set", G_CALLBACK(widget_state_set_bit), &(c->actuators[channel]));
	gtk_container_add(GTK_CONTAINER(cp->dw[channel].hbox), w);
	//gtk_box_pack_start(GTK_BOX(cp->dw[channel].hbox), w, TRUE, TRUE, 0);
}

int add_bitdevice(controlpanel *cp, controller *c, char *name)
{
	int i;

	switch (i = obit_add(c, name))
	{
		case CONTROLLER_INVALID_STATES:
			printf("obit_add() err=%d\n", i);
			break;
		case CONTROLLER_INVALID_ACTUATOR:
			printf("obit_add() err=%d\n", i);
			break;
		case CONTROLLER_FULL:
			printf("obit_add() err=%d\n", i);
			break;
		default:
			add_bitframe(cp, c, i);
			break;
	}

	return(i);
}

void add_pulseframe(controlpanel *cp, controller *c, int channel)
{
// frame
	cp->dw[channel].frame = gtk_frame_new(c->actuators[channel].name);
	//gtk_container_add(GTK_CONTAINER(ae->container), ae->frame);
	gtk_box_pack_start(GTK_BOX(cp->container), cp->dw[channel].frame, TRUE, TRUE, 0);

// horizontal box
	cp->dw[channel].hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_container_add(GTK_CONTAINER(cp->dw[channel].frame), cp->dw[channel].hbox);
	//gtk_box_pack_start(GTK_BOX(ae->frame), ae->hbox, TRUE, TRUE, 0);

	GtkWidget *w;

	cp->dw[channel].label = gtk_label_new(c->actuators[channel].name);
	//gtk_widget_set_size_request(cp->dw[channel].label, 100, 30);
	gtk_container_add(GTK_CONTAINER(cp->dw[channel].hbox), cp->dw[channel].label);

	cp->dw[channel].control = w = gtk_button_new_with_label(c->actuators[channel].name);
	g_signal_connect(GTK_BUTTON(w), "clicked", G_CALLBACK(button_clicked_pulse), &(c->actuators[channel]));
	gtk_container_add(GTK_CONTAINER(cp->dw[channel].hbox), w);
	//gtk_box_pack_start(GTK_BOX(cp->dw[channel].hbox), w, TRUE, TRUE, 0);
}

int add_pulsedevice(controlpanel *cp, controller *c, char *name)
{
	int i;

	switch (i = opulse_add(c, name))
	{
		case CONTROLLER_INVALID_STATES:
			printf("obit_add() err=%d\n", i);
			break;
		case CONTROLLER_INVALID_ACTUATOR:
			printf("obit_add() err=%d\n", i);
			break;
		case CONTROLLER_FULL:
			printf("obit_add() err=%d\n", i);
			break;
		default:
			add_pulseframe(cp, c, i);
			break;
	}

	return(i);
}

static gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data)
{

	return FALSE; // return FALSE to emit destroy signal
}

static void destroy(GtkWidget *widget, gpointer data)
{
	gtk_main_quit();
}

static void realize_cb(GtkWidget *widget, gpointer data)
{

}

void setup_default_icon(char *filename)
{
	GdkPixbuf *pixbuf;
	GError *err;

	err = NULL;
	pixbuf = gdk_pixbuf_new_from_file(filename, &err);

	if (pixbuf)
	{
		GList *list;      

		list = NULL;
		list = g_list_append(list, pixbuf);
		gtk_window_set_default_icon_list(list);
		g_list_free(list);
		g_object_unref(pixbuf);
	}
}

int main(int argc, char **argv)
{
	controller *c = NULL;
	int i;
	controlpanel cp;

	c = controller_open(V0, 0x00);
	if (c->err)
		printf("Open err=%d\n", c->err);

	setlocale(LC_ALL, "tr_TR.UTF-8");

	setup_default_icon("./images/controller.png");

	gtk_init(&argc, &argv);

	/* create a new window */
	cp.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(cp.window), GTK_WIN_POS_CENTER);
	gtk_container_set_border_width(GTK_CONTAINER(cp.window), 2);
	//gtk_widget_set_size_request(window, 100, 100);
	gtk_window_set_title(GTK_WINDOW(cp.window), "Controller");
	gtk_window_set_resizable(GTK_WINDOW(cp.window), TRUE);
	/* When the window is given the "delete-event" signal (this is given
	* by the window manager, usually by the "close" option, or on the
	* titlebar), we ask it to call the delete_event () function
	* as defined above. The data passed to the callback
	* function is NULL and is ignored in the callback function. */
	g_signal_connect(cp.window, "delete-event", G_CALLBACK (delete_event), NULL);
	/* Here we connect the "destroy" event to a signal handler.  
	* This event occurs when we call gtk_widget_destroy() on the window,
	* or if we return FALSE in the "delete-event" callback. */
	g_signal_connect(cp.window, "destroy", G_CALLBACK (destroy), NULL);
	g_signal_connect(cp.window, "realize", G_CALLBACK (realize_cb), NULL);

	cp.container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_container_add(GTK_CONTAINER(cp.window), cp.container);

	if ((i=add_channeldevice(&cp, c, "Motor", A_SWITCH, 0)) >= 0)
	{}
	if ((i=add_channeldevice(&cp, c, "Water Level", A_LEVEL, 8)) >= 0)
	{}


	if ((i=add_bitdevice(&cp, c, "Enable")) >= 0)
	{}

	if ((i=add_bitdevice(&cp, c, "LED")) >= 0)
	{}


	if ((i=add_pulsedevice(&cp, c, "Pulse 1")) >= 0)
	{}

	if ((i=add_pulsedevice(&cp, c, "Pulse 2")) >= 0)
	{}

	gtk_widget_show_all(cp.window);

	gtk_main();

	controller_close(c);
	c = NULL;

	return(0);

/*
	printf("ret=%d, c.aindex=%d, c.pins_used=%d\n", ochannel_add(&c, "", A_SWITCH, 0), c.aindex, c.channel_pins_used);
	printf("ret=%d, c.aindex=%d, c.pins_used=%d\n", ochannel_add(&c, "", A_SWITCH, 0), c.aindex, c.channel_pins_used);
	printf("ret=%d, c.aindex=%d, c.pins_used=%d\n", ochannel_add(&c, "", A_SWITCH, 0), c.aindex, c.channel_pins_used);
	//printf("base_pin=%d\n", c.actuators[c.aindex-1].base_pin);
	printf("ret=%d, c.aindex=%d, c.pins_used=%d\n", ochannel_add(&c, "", A_LEVEL, 8), c.aindex, c.channel_pins_used);
	//printf("base_pin=%d\n", c.actuators[c.aindex-1].base_pin);
	printf("ret=%d, c.aindex=%d, c.pins_used=%d\n", ochannel_add(&c, "", A_SWITCH, 0), c.aindex, c.channel_pins_used);
	printf("ret=%d, c.aindex=%d, c.pins_used=%d\n", ochannel_add(&c, "", A_SWITCH, 0), c.aindex, c.channel_pins_used);

	printf("ret=%d, c.bindex=%d\n", obit_add(&c, ""), c.bindex);
	printf("ret=%d, c.bindex=%d\n", obit_add(&c, ""), c.bindex);
	printf("ret=%d, c.bindex=%d\n", obit_add(&c, ""), c.bindex);

	ochannel_set_value(&c, 0, SWITCH_ON);
	ochannel_set_value(&c, 1, SWITCH_OFF);
	ochannel_set_value(&c, 2, SWITCH_ON);
	ochannel_set_value(&c, 3, 2);
	ochannel_set_value(&c, 4, SWITCH_ON);
	ochannel_set_value(&c, 5, SWITCH_ON);
	ochannel_write(&c);

	obit_set_value(&c, 9, SWITCH_ON);
	
	//obit_set_value(&c, 8, SWITCH_ON); // OE

	printf("ret=%d, c.pindex=%d\n", opulse_add(&c, ""), c.pindex);
	printf("ret=%d, c.pindex=%d\n", opulse_add(&c, ""), c.pindex);
	printf("ret=%d, c.pindex=%d\n", opulse_add(&c, ""), c.pindex);

	opulse_out(&c, 10);
*/

/*
	printf("ret=%d, c.aindex=%d, c.pins_used=%d\n", add_ochannel(&c, "", A_SWITCH, 0), c.aindex, c.channel_pins_used);
	printf("base_pin=%d\n", c.actuators[c.aindex-1].base_pin);

	printf("ret=%d, c.bindex=%d, c.pins_used=%d\n", add_obit(&c, ""), c.bindex, c.channel_pins_used);
	printf("ret=%d, c.bindex=%d, c.pins_used=%d\n", add_obit(&c, ""), c.bindex, c.channel_pins_used);
	printf("ret=%d, c.bindex=%d, c.pins_used=%d\n", add_obit(&c, ""), c.bindex, c.channel_pins_used);
	printf("base_pin=%d\n", c.actuators[c.bindex-1].base_pin);

	printf("ret=%d, c.pindex=%d, c.pins_used=%d\n", add_opulse(&c, ""), c.pindex, c.channel_pins_used);
	printf("ret=%d, c.pindex=%d, c.pins_used=%d\n", add_opulse(&c, ""), c.pindex, c.channel_pins_used);
	printf("ret=%d, c.pindex=%d, c.pins_used=%d\n", add_opulse(&c, ""), c.pindex, c.channel_pins_used);
	printf("base_pin=%d\n", c.actuators[c.pindex-1].base_pin);
*/
}
