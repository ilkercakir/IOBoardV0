#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include <locale.h>

#include "rules.h"
#include "devices.h"
#include "httpget.h"

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
	devicewidgets odw[12];
	devicewidgets idw[8];
	controller *c;
	iodevices *cha, *bit, *pul, *sen;
	httpclient h;
	int usegpio;
}controlpanel;

gboolean widget_state_set_gpio(GtkWidget *togglebutton, gboolean state, gpointer data)
{
	actuator *a = (actuator*)data;

	ochannel_set_value(a->parent, a->channel, (state?0x01:0x00));
	ochannel_write(a->parent);

//printf("channel %d value %c\n", a->channel, (ochannel_get_value(a->parent, a->channel)?'1':'0'));

	return(TRUE);
}

gboolean widget_state_set_http(GtkWidget *togglebutton, gboolean state, gpointer data)
{
	actuator *a = (actuator*)data;

	httpclient h;
	jsonWriteChannel(&h, a->channel, 0, (state?0x01:0x00));

//printf("channel %d value %c\n", a->channel, (ochannel_get_value(a->parent, a->channel)?'1':'0'));

	return(TRUE);
}

void combo_changed_gpio(GtkWidget *combo, gpointer data)
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

void combo_changed_http(GtkWidget *combo, gpointer data)
{
	actuator *a = (actuator*)data;
	gchar *strval;

	g_object_get((gpointer)combo, "active-id", &strval, NULL);
	//printf("Selected id %s\n", strval);
	a->value = atoi((const char *)strval);
	g_free(strval);

	httpclient h;
	jsonWriteChannel(&h, a->channel, 0, a->value);

//printf("channel %d value %c\n", a->channel, ochannel_get_value(a->parent, a->channel) + '0');
}

gboolean widget_state_set_bit_gpio(GtkWidget *togglebutton, gboolean state, gpointer data)
{
	actuator *a = (actuator*)data;
	switch_values value = (state?SWITCH_ON:SWITCH_OFF);

	obit_set_value(a->parent, a->channel, value);

//printf("bit %d value %c\n", a->channel, (obit_get_value(a->parent, a->channel)?'1':'0'));

	return(TRUE);
}

gboolean widget_state_set_bit_http(GtkWidget *togglebutton, gboolean state, gpointer data)
{
	actuator *a = (actuator*)data;
	switch_values value = (state?SWITCH_ON:SWITCH_OFF);

	httpclient h;
	jsonWriteBit(&h, a->channel, 0, value);

//printf("bit %d value %c\n", a->channel, (obit_get_value(a->parent, a->channel)?'1':'0'));

	return(TRUE);
}

static void button_clicked_pulse_gpio(GtkWidget *button, gpointer data)
{
	actuator *a = (actuator*)data;

	opulse_out(a->parent, a->channel, (int)a->value*100000);
}

static void button_clicked_pulse_http(GtkWidget *button, gpointer data)
{
	actuator *a = (actuator*)data;

	httpclient h;
	jsonWritePulse(&h, a->channel, 0, a->value);
}

void add_ochannelframe(controlpanel *cp, controller *c, int channel)
{
// frame
	cp->odw[channel].frame = gtk_frame_new(c->actuators[channel].name);
	//gtk_container_add(GTK_CONTAINER(ae->container), ae->frame);
	gtk_box_pack_start(GTK_BOX(cp->container), cp->odw[channel].frame, TRUE, TRUE, 0);

// horizontal box
	cp->odw[channel].hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_container_add(GTK_CONTAINER(cp->odw[channel].frame), cp->odw[channel].hbox);
	//gtk_box_pack_start(GTK_BOX(ae->frame), ae->hbox, TRUE, TRUE, 0);

	GtkWidget *w;

	cp->odw[channel].label = gtk_label_new(c->actuators[channel].name);
	//gtk_widget_set_size_request(cp->dw[channel].label, 100, 30);
	gtk_container_add(GTK_CONTAINER(cp->odw[channel].hbox), cp->odw[channel].label);

	switch (c->actuators[channel].type)
	{
		case A_LEVEL:
			cp->odw[channel].control = w = gtk_combo_box_text_new();

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
			if (cp->usegpio)
				g_signal_connect(GTK_COMBO_BOX(w), "changed", G_CALLBACK(combo_changed_gpio), &(c->actuators[channel]));
			else
				g_signal_connect(GTK_COMBO_BOX(w), "changed", G_CALLBACK(combo_changed_http), &(c->actuators[channel]));
			gtk_container_add(GTK_CONTAINER(cp->odw[channel].hbox), w);
			//gtk_box_pack_start(GTK_BOX(ae->parameter[i].vbox), w, TRUE, TRUE, 0);
			break;
		case A_SWITCH:
		case A_PULSE:
		default:
			cp->odw[channel].control = w = gtk_switch_new();
			gtk_switch_set_active(GTK_SWITCH(w), c->actuators[channel].value);
			if (cp->usegpio)
				g_signal_connect(GTK_SWITCH(w), "state-set", G_CALLBACK(widget_state_set_gpio), &(c->actuators[channel]));
			else
				g_signal_connect(GTK_SWITCH(w), "state-set", G_CALLBACK(widget_state_set_http), &(c->actuators[channel]));
			gtk_container_add(GTK_CONTAINER(cp->odw[channel].hbox), w);
			//gtk_box_pack_start(GTK_BOX(cp->dw[channel].hbox), w, TRUE, TRUE, 0);
			break;
	}
}

int add_ochanneldevice(controlpanel *cp, controller *c, char *name, actuator_type type, int nstates, unsigned char initval)
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
			if (cp->usegpio)
				ochannel_set_value(c, i, initval);
			else
				ochannel_set_value(c, i, jsonChannelGetValue(&(cp->h), i, 0));
			add_ochannelframe(cp, c, i);
			break;
	}

	return(i);
}

void add_obitframe(controlpanel *cp, controller *c, int channel)
{
// frame
	cp->odw[channel].frame = gtk_frame_new(c->actuators[channel].name);
	//gtk_container_add(GTK_CONTAINER(ae->container), ae->frame);
	gtk_box_pack_start(GTK_BOX(cp->container), cp->odw[channel].frame, TRUE, TRUE, 0);

// horizontal box
	cp->odw[channel].hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_container_add(GTK_CONTAINER(cp->odw[channel].frame), cp->odw[channel].hbox);
	//gtk_box_pack_start(GTK_BOX(ae->frame), ae->hbox, TRUE, TRUE, 0);

	GtkWidget *w;

	cp->odw[channel].label = gtk_label_new(c->actuators[channel].name);
	//gtk_widget_set_size_request(cp->dw[channel].label, 100, 30);
	gtk_container_add(GTK_CONTAINER(cp->odw[channel].hbox), cp->odw[channel].label);

	cp->odw[channel].control = w = gtk_switch_new();
	gtk_switch_set_active(GTK_SWITCH(w), c->actuators[channel].value);
	if (cp->usegpio)
		g_signal_connect(GTK_SWITCH(w), "state-set", G_CALLBACK(widget_state_set_bit_gpio), &(c->actuators[channel]));
	else
		g_signal_connect(GTK_SWITCH(w), "state-set", G_CALLBACK(widget_state_set_bit_http), &(c->actuators[channel]));
	gtk_container_add(GTK_CONTAINER(cp->odw[channel].hbox), w);
	//gtk_box_pack_start(GTK_BOX(cp->dw[channel].hbox), w, TRUE, TRUE, 0);
}

int add_obitdevice(controlpanel *cp, controller *c, char *name, unsigned char initval)
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
			if (cp->usegpio)
				obit_set_value(c, i, initval);
			else
				c->actuators[i].value = jsonBitGetValue(&(cp->h), i, 0);
			add_obitframe(cp, c, i);
			break;
	}

	return(i);
}

void add_opulseframe(controlpanel *cp, controller *c, int channel)
{
// frame
	cp->odw[channel].frame = gtk_frame_new(c->actuators[channel].name);
	//gtk_container_add(GTK_CONTAINER(ae->container), ae->frame);
	gtk_box_pack_start(GTK_BOX(cp->container), cp->odw[channel].frame, TRUE, TRUE, 0);

// horizontal box
	cp->odw[channel].hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_container_add(GTK_CONTAINER(cp->odw[channel].frame), cp->odw[channel].hbox);
	//gtk_box_pack_start(GTK_BOX(ae->frame), ae->hbox, TRUE, TRUE, 0);

	GtkWidget *w;

	cp->odw[channel].label = gtk_label_new(c->actuators[channel].name);
	//gtk_widget_set_size_request(cp->dw[channel].label, 100, 30);
	gtk_container_add(GTK_CONTAINER(cp->odw[channel].hbox), cp->odw[channel].label);

	cp->odw[channel].control = w = gtk_button_new_with_label(c->actuators[channel].name);
	if (cp->usegpio)
		g_signal_connect(GTK_BUTTON(w), "clicked", G_CALLBACK(button_clicked_pulse_gpio), &(c->actuators[channel]));
	else
		g_signal_connect(GTK_BUTTON(w), "clicked", G_CALLBACK(button_clicked_pulse_http), &(c->actuators[channel]));
	gtk_container_add(GTK_CONTAINER(cp->odw[channel].hbox), w);
	//gtk_box_pack_start(GTK_BOX(cp->dw[channel].hbox), w, TRUE, TRUE, 0);
}

int add_opulsedevice(controlpanel *cp, controller *c, char *name, unsigned char initval)
{
	int i;

	switch (i = opulse_add(c, name))
	{
		case CONTROLLER_INVALID_STATES:
			printf("opulse_add() err=%d\n", i);
			break;
		case CONTROLLER_INVALID_ACTUATOR:
			printf("opulse_add() err=%d\n", i);
			break;
		case CONTROLLER_FULL:
			printf("opulse_add() err=%d\n", i);
			break;
		default:
			if (cp->usegpio)
				opulse_set_value(c, i, initval);
			else
				c->actuators[i].value = jsonPulseGetValue(&(cp->h), i, 0);
			add_opulseframe(cp, c, i);
			break;
	}

	return(i);
}

void add_ichannelframe(controlpanel *cp, controller *c, int channel)
{
// frame
	cp->idw[channel].frame = gtk_frame_new(c->sensors[channel].name);
	//gtk_container_add(GTK_CONTAINER(ae->container), ae->frame);
	gtk_box_pack_start(GTK_BOX(cp->container), cp->idw[channel].frame, TRUE, TRUE, 0);

// horizontal box
	cp->idw[channel].hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_container_add(GTK_CONTAINER(cp->idw[channel].frame), cp->idw[channel].hbox);
	//gtk_box_pack_start(GTK_BOX(ae->frame), ae->hbox, TRUE, TRUE, 0);

	GtkWidget *w;

	cp->idw[channel].label = gtk_label_new(c->sensors[channel].name);
	//gtk_widget_set_size_request(cp->dw[channel].label, 100, 30);
	gtk_container_add(GTK_CONTAINER(cp->idw[channel].hbox), cp->idw[channel].label);

	switch (c->sensors[channel].type)
	{
		case S_LEVEL:
			cp->idw[channel].control = w = gtk_combo_box_text_new();

			int i;
			char s[10];
			for(i=0;i<c->sensors[channel].numstates;i++)
			{
				sprintf(s, "%d", i);
				//printf("val = %s\n", s);
				gchar *gc = g_strnfill(10, '\0');
				g_stpcpy(gc, (const char *)s);
				gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(w), gc, gc);
				g_free(gc);
			}
			sprintf(s, "%d", c->sensors[channel].value);
			g_object_set((gpointer)w, "active-id", s, NULL);
			//g_signal_connect(GTK_COMBO_BOX(w), "changed", G_CALLBACK(), &(c->sensors[channel]));
			gtk_container_add(GTK_CONTAINER(cp->idw[channel].hbox), w);
			//gtk_box_pack_start(GTK_BOX(ae->parameter[i].vbox), w, TRUE, TRUE, 0);
			break;
		case S_SWITCH:
		default:
			cp->idw[channel].control = w = gtk_switch_new();
			gtk_switch_set_active(GTK_SWITCH(w), c->sensors[channel].value);
			//g_signal_connect(GTK_SWITCH(w), "state-set", G_CALLBACK(), &(c->sensors[channel]));
			gtk_container_add(GTK_CONTAINER(cp->idw[channel].hbox), w);
			//gtk_box_pack_start(GTK_BOX(cp->dw[channel].hbox), w, TRUE, TRUE, 0);
			break;
	}
}

int add_ichanneldevice(controlpanel *cp, controller *c, char *name, sensor_type type, int nstates)
{
	int i;

	switch (i = ichannel_add(c, name, type, nstates))
	{
		case CONTROLLER_INVALID_STATES:
			printf("ichannel_add() err=%d\n", i);
			break;
		case CONTROLLER_INVALID_ACTUATOR:
			printf("ichannel_add() err=%d\n", i);
			break;
		case CONTROLLER_FULL:
			printf("ichannel_add() err=%d\n", i);
			break;
		default:
			if (cp->usegpio)
				ichannel_read(c);
			else
				c->sensors[i].value = jsonReadChannel(&(cp->h), i, 0);
			add_ichannelframe(cp, c, i);
	}

	return(i);
}

static void arbutton_clicked_gpio(GtkWidget *button, gpointer data)
{
	controlpanel* cp = (controlpanel *)data;
	controller *c = cp->c;
	int i;
	GtkWidget *w;
	char s[10];

	for(i=0;c->actuators[i].type!=A_VOID;i++)
	{
		w = cp->odw[i].control;
		switch (c->actuators[i].type)
		{
			case A_LEVEL:
				sprintf(s, "%d", c->actuators[i].value);
				g_object_set((gpointer)w, "active-id", s, NULL);
				break;
			case A_SWITCH:
			default:
				gtk_switch_set_active(GTK_SWITCH(w), c->actuators[i].value);
				break;
		}
		//printf("%s = %c\n", c->sensors[i].name, ichannel_get_value(c, i) + '0');
	}
//printf("ichannel_get_value(0) = %d\n", ichannel_get_value(c, 0));
}

static void arbutton_clicked_http(GtkWidget *button, gpointer data)
{
	controlpanel* cp = (controlpanel *)data;
	controller *c = cp->c;
	iodevices *cha = cp->cha;
	iodevices *bit = cp->bit;
	int i, channel;
	GtkWidget *w;
	char s[10];

	for(i=0;i<cha->count;i++)
	{
		channel = cha->devices[i].chnnl;
		w = cp->odw[channel].control;
		c->actuators[channel].value = jsonChannelGetValue(&(cp->h), channel, 0);
		switch (c->actuators[channel].type)
		{
			case A_LEVEL:
				sprintf(s, "%d", c->actuators[channel].value);
				g_object_set((gpointer)w, "active-id", s, NULL);
				break;
			case A_SWITCH:
			default:
				gtk_switch_set_active(GTK_SWITCH(w), c->actuators[channel].value);
				break;
		}
		//printf("%s = %c\n", c->sensors[i].name, ichannel_get_value(c, i) + '0');
	}
//printf("ichannel_get_value(0) = %d\n", ichannel_get_value(c, 0));

	for(i=0;i<bit->count;i++)
	{
		channel = bit->devices[i].chnnl;
		w = cp->odw[channel].control;
		c->actuators[channel].value = jsonBitGetValue(&(cp->h), channel, 0);
		switch (c->actuators[channel].type)
		{
			case A_LEVEL:
				sprintf(s, "%d", c->actuators[channel].value);
				g_object_set((gpointer)w, "active-id", s, NULL);
				break;
			case A_SWITCH:
			default:
				gtk_switch_set_active(GTK_SWITCH(w), c->actuators[channel].value);
				break;
		}
		//printf("%s = %c\n", c->sensors[i].name, ichannel_get_value(c, i) + '0');
	}
}

static void srbutton_clicked_gpio(GtkWidget *button, gpointer data)
{
	controlpanel* cp = (controlpanel *)data;
	controller *c = cp->c;
	int i;
	GtkWidget *w;
	char s[10];

	ichannel_read(c);

	for(i=0;c->sensors[i].type!=S_VOID;i++)
	{
		w = cp->idw[i].control;
		switch (c->sensors[i].type)
		{
			case S_LEVEL:
				sprintf(s, "%d", c->sensors[i].value);
				g_object_set((gpointer)w, "active-id", s, NULL);
				break;
			case S_SWITCH:
			default:
				gtk_switch_set_active(GTK_SWITCH(w), c->sensors[i].value);
				break;
		}
		//printf("%s = %c\n", c->sensors[i].name, ichannel_get_value(c, i) + '0');
	}
	
//printf("ichannel_get_value(0) = %d\n", ichannel_get_value(c, 0));
}

static void srbutton_clicked_http(GtkWidget *button, gpointer data)
{
	controlpanel* cp = (controlpanel *)data;
	controller *c = cp->c;
	iodevices *sen = cp->sen;
	int i;
	GtkWidget *w;
	char s[10];

	for(i=0;i<sen->count;i++)
	{
		w = cp->idw[i].control;
		c->sensors[i].value = jsonReadChannel(&(cp->h), i, 0);
		switch (c->sensors[i].type)
		{
			case S_LEVEL:
				sprintf(s, "%d", c->sensors[i].value);
				g_object_set((gpointer)w, "active-id", s, NULL);
				break;
			case S_SWITCH:
			default:
				gtk_switch_set_active(GTK_SWITCH(w), c->sensors[i].value);
				break;
		}
		//printf("%s = %c\n", c->sensors[i].name, ichannel_get_value(c, i) + '0');
	}
	
//printf("ichannel_get_value(0) = %d\n", ichannel_get_value(c, 0));
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
	int i, err;
	controlpanel cp;
	scheduler s;
	iodevices cha, bit, pul, sen;
	int usegpio = 0;

	setlocale(LC_ALL, "tr_TR.UTF-8");
	setup_default_icon("./images/controller.png");

	if (argc>1)
	{
		if (!strcmp(argv[1], "gpio"))
		{
			usegpio = 1;
		}
	}
	cp.usegpio = usegpio;

	c = controller_open(V0, 0x00, usegpio);
	if (c->err)
		printf("Open err=%d\n", c->err);
	cp.c = c;

	cp.cha = &cha;
	cp.bit = &bit;
	cp.pul = &pul;
	cp.sen = &sen;

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

	get_devices(&cha, 'A', 0, 7);
	for(i=0;i<cha.count;i++)
	{
		//printf("channel %d, id=%d\n", i, cha.devices[i].devid);
		if ((err=add_ochanneldevice(&cp, c, cha.devices[i].dtext, cha.devices[i].dtype, (cha.devices[i].dstat?cha.devices[i].dstat:cha.devices[i].numstates), cha.devices[i].initval)) >= 0)
		{}
	}
	if (usegpio)
		ochannel_write(c);

	get_devices(&bit, 'A', 8, 9);
	for(i=0;i<bit.count;i++)
	{
		//printf("bit %d, id=%d\n", i, bit.devices[i].devid);
		if ((err=add_obitdevice(&cp, c, bit.devices[i].dtext, bit.devices[i].initval)) >= 0)
		{}
	}

	get_devices(&pul, 'A', 10, 11);
	for(i=0;i<pul.count;i++)
	{
		//printf("pulse %d, id=%d\n", i, pul.devices[i].devid);
		if ((err=add_opulsedevice(&cp, c, pul.devices[i].dtext, pul.devices[i].initval)) >= 0)
		{}
	}

	GtkWidget *arbutton;
	arbutton = gtk_button_new_with_label("Refresh");
	if (usegpio)
		g_signal_connect(GTK_BUTTON(arbutton), "clicked", G_CALLBACK(arbutton_clicked_gpio), (void *)&cp);
	else
		g_signal_connect(GTK_BUTTON(arbutton), "clicked", G_CALLBACK(arbutton_clicked_http), (void *)&cp);
	gtk_container_add(GTK_CONTAINER(cp.container), arbutton);

	get_devices(&sen, 'S', 0, 7);
	for(i=0;i<sen.count;i++)
	{
		//printf("sensor %d, id=%d\n", i, sen.devices[i].devid);
		if ((err=add_ichanneldevice(&cp, c, sen.devices[i].dtext, sen.devices[i].dtype, (sen.devices[i].dstat?sen.devices[i].dstat:sen.devices[i].numstates))) >= 0)
		{}
	}

	GtkWidget *srbutton;
	srbutton = gtk_button_new_with_label("Refresh");
	if (usegpio)
		g_signal_connect(GTK_BUTTON(srbutton), "clicked", G_CALLBACK(srbutton_clicked_gpio), (void *)&cp);
	else
		g_signal_connect(GTK_BUTTON(srbutton), "clicked", G_CALLBACK(srbutton_clicked_http), (void *)&cp);
	gtk_container_add(GTK_CONTAINER(cp.container), srbutton);

	gtk_widget_show_all(cp.window);

	if (usegpio)
		init_scheduler(&s, c);
	else
		init_scheduler(&s, NULL);

	gtk_main();

	close_scheduler(&s);

	free_devices(&cha);
	free_devices(&bit);
	free_devices(&pul);
	free_devices(&sen);

	controller_close(c);

	return(0);
}
