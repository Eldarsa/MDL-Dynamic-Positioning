"use strict";

; (function (phidget22) {

	/**************************************************************************************************
	 * ControlPanel
	 */

	phidget22.ControlPanel = function (div) {

		var self = this;

		this.ppdata = null;

		this.basediv = div;
		this.userdiv = '#' + div;

		var treediv = this.basediv + '_body';
		this.treediv = '#' + treediv;

		/* centralize div id creation */
		this.mkDiv = function (obj, isVintPort) {

			if (isVintPort)
				return ('vint_port_' + obj.getHub().getKey() + '_' + obj.getHubPort());

			if (obj instanceof phidget22.Connection)
				return ('conn_' + this.basediv + '_' + obj.id);
			else if (obj instanceof phidget22.Phidget) {
				if (obj.getIsChannel())
					return ('ch_' + this.basediv + '_' + obj.getKey());
				else
					return ('dev_' + this.basediv + '_' + obj.getKey());
			}
		}

		this.mkDialogDiv = function (ch, suffix) {

			return (this.basediv + '_' + ch.getKey() + suffix);
		}

		this.showOrHideVintPortDevices = function (port) {

			var vintDeviceAttached = false;
			for (var c in port.children) {
				var dev = jstree.get_node(port.children[c]);

				if (!dev.data.obj.getIsHubPortDevice()) {
					vintDeviceAttached = true;
					break;
				}
			}

			if (vintDeviceAttached)
				jstree.open_node(port);

			for (var c in port.children) {
				var dev = jstree.get_node(port.children[c]);
				if (dev.data.obj.getIsHubPortDevice()) {
					if (vintDeviceAttached && !jstree.is_hidden(dev))
						jstree.hide_node(dev);
					else if (!vintDeviceAttached && jstree.is_hidden(dev))
						jstree.show_node(dev);
				}
			}
		}
		if (!$.jstree)
			throw (new Error("missing jquery jstree"));

		$(this.userdiv).html(
			'<div class="PhidgetControlPanel" id="' + this.basediv + '">' +
			'<div class="PhidgetControlPanelHeader" id="' + this.basediv + '_header">Phidget22 JavaScript Control Panel</div>' +
			'<div class="PhidgetControlPanelBody" id="' + this.basediv + '_body"></div>' +
			'<div class="PhidgetControlPanelFooter" id="' + this.basediv + '_footer">Double Click to Launch UI</div>' +
			'<div id="' + this.basediv + '_dialogs"></div>' +
			'<div id="error_dialog"></div>' +
			'</div>'
		);

		var tree = {
			core: {
				check_callback: true,
				dblclick_toggle: false
			},
			plugins: ['grid', 'contextmenu', 'sort'],
			contextmenu: {
				items: function (node) {

					var menu = {};
					var chnode;

					var openItem = {
						label: 'Open',
						action: function (obj) {
							self.openChannel(chnode);
						}
					}

					if (node.id.startsWith('dev_')) {
						if (node.data && node.data.obj) {
							if (node.data.obj.getDeviceClass() !== phidget22.DeviceClass.VINT) {

								menu.setlabel = {
									label: 'Set Label...',
									action: function (obj) {
										self.writeLabel(node);
									}
								};
							}
						}
					}

					if (node.id.startsWith('ch_')) {
						chnode = node;
						if (chnode.data && chnode.data.obj)
							menu.open = openItem;
					} else if (node.data.channel === 0) {
						chnode = jstree.get_node(node.children[0]);
						if (chnode.data && chnode.data.obj)
							menu.open = openItem;
					} else if (node.id.startsWith('conn_')) {
						var conn = phidget22.Connections[node.id.substring(6 + self.basediv.length)];
						if (conn.connected) {
							menu.close = {
								label: 'Close',
								action: function (obj) {
									this.close();
								}.bind(conn)
							};
						} else {
							menu.connect = {
								label: 'Connect',
								action: function (obj) {
									this.connect();
								}.bind(conn)
							};
						}
					}

					return (menu);
				}
			},
			sort: function (a, b) {
				var nodea = jstree.get_node(a);
				var nodeb = jstree.get_node(b);

				if (nodea.text !== nodeb.text)
					return (nodea.text > nodeb.text ? 1 : -1);

				if (nodea.data.serial !== nodeb.data.serial)
					return (nodea.data.serial > nodeb.data.serial ? 1 : -1);

				if (nodea.data.channel !== nodeb.data.channel)
					return (nodea.data.channel > nodeb.data.channel ? 1 : -1);

				return (this.get_text(a) > this.get_text(b) ? 1 : -1);
			},
			grid: {
				columns: [
					{
						header: 'name',
						//width: 99%
					},
					{
						header: 'SKU',
						value: 'sku',
						width: 120
					},
					{
						header: 'Serial #',
						value: 'serial',
						cellClass: 'cell-right-align',
						width: 75
					},
					{
						header: 'Label',
						value: 'label',
						width: 120
					},
					{
						header: 'Channel',
						value: 'channel',
						cellClass: 'cell-right-align',
						width: 60
					},
					{
						header: 'Version',
						value: 'version',
						cellClass: 'cell-right-align',
						width: 60
					}
				],
				//resizable: true,
				//height: 600
			}
		};

		$(this.treediv).jstree(tree);
		var jstree = $(this.treediv).jstree(true);

		$(this.treediv).dblclick(nodeDoubleClicked);

		/*
		* Create a manager to find out about channels.
		*/
		var manager = new phidget22.Manager({
			onDeviceAttach: this.add.bind(this),
			onDeviceDetach: this.remove.bind(this),
			onAttach: this.add.bind(this),
			onDetach: this.remove.bind(this)
		});
		manager.open();

		/* Existing connections */
		for (var c in phidget22.Connections)
			this.add(phidget22.Connections[c]);

		/* Future connections */
		phidget22.onConnectionAdded = this.add.bind(this);
		phidget22.onConnectionRemoved = this.remove.bind(this);

		function nodeDoubleClicked(e) {

			var $node = $(e.target).closest('li');
			var id = $node.attr('id');
			if (!id)
				return;

			var node = jstree.get_node(id);

			if (id.startsWith('ch_')) {
				self.openChannel(node);
				return;
			}
			if (node.data.channel === 0) {
				node = jstree.get_node(node.children[0]);
				self.openChannel(node);
				return;
			}

			if (node.data.channel !== 0)
				jstree.toggle_node(node);
		}
	}

	phidget22.ControlPanel.prototype.writeLabel = function (node) {

		var jstree = $(this.treediv).jstree(true);

		// Find a channel child
		for (var n in node.children) {
			n = jstree.get_node(node.children[n]);
			if (n.data.obj instanceof phidget22.Phidget && n.data.obj.getIsChannel()) {
				this.openChannel(n, true);
				return;
			}
		}
	}

	phidget22.ControlPanel.prototype.openChannel = function (node, writeLabel) {

		var jstree = $(this.treediv).jstree(true);
		var phid = node.data.obj;

		if (node.data.phidget) {
			// Already opening
			return;
		}

		node.data.phidget = phid;

		phid.onError = function (code, msg) {

			// Handle this error - it probably means the Phidget is open elsewhere
			// NOTE: it's only safe to handle this because we are specifing a specific channel we want to open
			if (code == phidget22.ErrorCode.BUSY || code == phidget22.ErrorCode.ACCESS) {

				// close so the library doesn't keep trying to open this channel
				phid.close();
				delete node.data.phidget;

				$("#error_dialog").html("<p>Unable to open Phidget: " + msg + "<\p><p>This channel may be open elsewhere, or you may not have access.<\p>");
				$("#error_dialog").dialog({
					title: "Unable to open",
					height: 'auto',
					close: function () {
						$("#error_dialog").empty();
					}
				});

				return;
			}

			console.error("Error event during open", msg);
		}

		phid.onAttach = function (phid) {
			this.render(phid, writeLabel);
		}.bind(this);

		phid.onDetach = function (phid) {
			if (!phid.isopen)
				return;
			if (typeof PhidgetPanel !== 'undefined')
				PhidgetPanel.toggle(phid, this.mkDialogDiv(phid, ''));
			delete node.data.phidget;
		}.bind(this);

		phid.open(phidget22.DEFAULT_TIMEOUT).catch(function (err) {
			if (err.errorCode == phidget22.ErrorCode.TIMEOUT) {

				$("#error_dialog").html("<p>Unable to open Phidget because of a Timeout.<\p>");
				$("#error_dialog").dialog({
					title: "Unable to open",
					height: 'auto',
					close: function () {
						$("#error_dialog").empty();
					}
				});

				return;
			}

			console.log("Open didn't complete: " + err.message);
		});
	}

	phidget22.ControlPanel.prototype.render = function (phid, writeLabel) {

		var self = this;
		if (this.ppdata === null) {
			/*
			 * Load PhidgetPanel.
			 */
			$.get('/controlpanel/PhidgetPanel.html', function (data) {
				self.ppdata = data;
				self.render(phid, writeLabel);
			});
			return;
		}

		// Channel may have detached while loading PhidgetPanel
		if (!phid.getAttached())
			return;

		var key = this.mkDialogDiv(phid, '');

		var ppdiv = $('#' + this.mkDialogDiv(phid, '_phidgetpanel_content'));
		if (ppdiv.length) {
			var example = window[phid.getChannelClassName().substring(7) + 'Example'];
			if (!example)
				throw (phid.getChannelClassName().substring(7) + ' Example not found');
			example.setup(phid);
			PhidgetPanel.toggle(phid, key);
			return;
		}

		var ddiv = $('#' + this.mkDialogDiv(phid, '_dialog'));

		var data = this.ppdata.replace(/\$KEY/g, self.basediv + '_' + phid.getKey());
		ddiv.hide();
		ddiv.html(data);
		PhidgetPanel.setup(phid, key);
		PhidgetPanel.toggle(phid, key);

		var ppdiv = $('#' + this.mkDialogDiv(phid, '_phidgetpanel_content'));

		var exname = phid.getChannelClassName().substring(7);
		if (phid.getChannelClass() === phidget22.ChannelClass.DICTIONARY && phid.getDeviceSerialNumber() == 2)
			exname = 'ControlDictionary';

		if (writeLabel === true)
			exname = 'WriteLabel';

		$.get('/controlpanel/' + exname + '.html', function (data) {

			// Channel may have detached while loading example
			if (!phid.getAttached())
				return;

			data = data.replace(/\$KEY/g, key);
			ppdiv.empty();
			ppdiv.html(data);
			var example = window[exname + 'Example'];
			if (!example)
				throw (exname + ' Example not found');
			example.setup(phid);

			ddiv.dialog({
				title: writeLabel ? 'Write Label' : phid.getChannelName(),
				autoOpen: false,
				modal: false,
				show: "blind",
				hide: "blind",
				width: example.width ? example.width : 'auto',
				height: 'auto',
				autoResize: true,
				open: function () { },
				close: function () {
					if (phid.isopen) {
						if (writeLabel) {
							var jstree = $(self.treediv).jstree(true);
							var parentnode = jstree.get_node(self.mkDiv(phid.getParent()));
							parentnode.data.label = phid.getDeviceLabel();
							jstree.redraw_node(parentnode);
						}
						phid.close();
					}
					if (example.teardown)
						example.teardown(phid);
					ddiv.empty();
				}
			});
			ddiv.show();
			ddiv.dialog('open');
		});
	}

	phidget22.ControlPanel.prototype.add = function (obj) {

		var jstree = $(this.treediv).jstree(true);

		var nodeid = this.mkDiv(obj);
		var node = jstree.get_node(nodeid);

		/*
		 * If there is a user phidget attached, we are waiting for a device that was attached
		 * and then went away, but was not closed by the control panel; otherwise, this is
		 * a bug.
		 */
		if (node !== false)
			return;

		if (obj instanceof phidget22.Phidget) {
			if (obj.getIsChannel()) {
				var ch = obj;

				var node = {
					id: this.mkDiv(ch),
					text: ch.getChannelName(),
					data: {
						channel: ch.getChannel()
					}
				};
				var parent = '#' + this.mkDiv(ch.getParent());

				if (node = jstree.create_node(parent, node, 'last')) {
					jstree.get_node(node).data.obj = ch;
				} else
					throw (new Error('failed to add new node for channel: ' + ch));

				jstree.hide_icon(node);

				var parentnode = jstree.get_node(this.mkDiv(ch.getParent()));
				if (parentnode.children.length > 1) {
					for (var c in parentnode.children) {
						var childnode = jstree.get_node(parentnode.children[c]);
						if (jstree.is_hidden(childnode))
							jstree.show_node(childnode);
					}
					if (parentnode.data.channel === 0) {
						parentnode.data.channel = '';
						jstree.redraw_node(parentnode);
					}
				} else {
					jstree.hide_node(node);
				}

				// Hide HUB channels
				if (ch.getChannelClass() === phidget22.ChannelClass.HUB)
					jstree.hide_node(node);

				/*
				 * Add the dialog div.
				 */
				var ddiv = this.mkDialogDiv(ch, '_dialog');
				var cdiv = this.mkDialogDiv(ch, '_dialog_content');
				if ($('#' + ddiv).length === 0) {
					var dsdiv = $('#' + this.basediv + '_dialogs');
					dsdiv.append('<div id="' + ddiv + '"><div id="' + cdiv + '"></div></div>');
				}
			} else {
				var dev = obj;

				var node = {
					id: nodeid,
					text: dev.getDeviceName(),
					data: {
						version: dev.getDeviceVersion(),
						channel: 0
					}
				};

				switch (dev.device.type) {
					case 'VINT':
						node.icon = '/controlpanel/style/vint.png';
						if (!dev.getIsHubPortDevice())
							node.data.sku = dev.getDeviceSKU();
						break;
					case 'MESH':
					case 'USB':
					case 'SPI':
					case 'LIGHTNING':
						node.icon = '/controlpanel/style/usb.png';
						node.data.serial = dev.getDeviceSerialNumber();
						node.data.label = dev.getDeviceLabel();
						node.data.sku = dev.getDeviceSKU();
						break;
					case 'VIRTUAL':
						node.icon = '/controlpanel/style/virtual.png';
						node.data.serial = dev.getDeviceSerialNumber();
						node.data.label = dev.getDeviceLabel();
						break;
				}

				if (dev.getDeviceClass() === phidget22.DeviceClass.HUB)
					node.state = { opened: true };

				if (dev.getDeviceClass() === phidget22.DeviceClass.VINT) {
					var portid = this.mkDiv(dev, true);
					var port = jstree.get_node(portid);
					if (!port) {
						var parent = '#' + this.mkDiv(dev.getParent());
						var pnode = {
							id: portid,
							text: 'Port ' + dev.getHubPort(),
							icon: '/controlpanel/style/vint.png',
							data: {}
						};
						portid = jstree.create_node(parent, pnode, 'last');
						if (!portid)
							throw (new Error('failed to add new hub port node'));
					}
					if (node = jstree.create_node(portid, node, 'last'))
						jstree.get_node(node).data.obj = dev;
					else
						throw (new Error('failed to add new node for vint device: ' + dev));

					if (dev.getIsHubPortDevice())
						jstree.hide_icon(node);

					this.showOrHideVintPortDevices(port);
				} else {
					if (dev.getParent())
						var parent = '#' + this.mkDiv(dev.getParent());
					else
						var parent = '#' + this.mkDiv(dev.device.conn);
					if (node = jstree.create_node(parent, node, 'last'))
						jstree.get_node(node).data.obj = dev;
					else
						throw (new Error('failed to add new node for device: ' + dev));
				}
			}
		} else if (obj instanceof phidget22.Connection) {
			var conn = obj;

			var node = {
				id: this.mkDiv(conn),
				text: conn.name,
				icon: '/controlpanel/style/net.png',
				state: { opened: true },
				children: [],
				data: {}
			};

			var node = jstree.create_node(null, node, 'last');
		}
	}

	phidget22.ControlPanel.prototype.remove = function (obj) {

		if (obj instanceof phidget22.Phidget) {

			var jstree = $(this.treediv).jstree(true);
			var nodeid = this.mkDiv(obj);
			var node = jstree.get_node(nodeid);
			if (node === false) {
				console.log('unable to find node for:' + obj + ' (' + nodeid + ')');
				return;
			}

			/*
			 * We do not remove nodes with children just to enforce strict handing of the
			 * tree in the rest of the code.
			 */
			if (!jstree.is_leaf(node)) {
				console.log('node ' + obj + ' still has children!');
				return;
			}
			if (node.data.phidget)
				delete node.data.phidget;
			jstree.delete_node(node);

			/*
			 * Remove the 'Port #' node if it is now empty.
			 */
			if (!obj.getIsChannel() && obj.getDeviceClass() === phidget22.DeviceClass.VINT) {
				var portid = this.mkDiv(obj, true);
				var node = jstree.get_node(portid);
				if (node === false)
					return;
				if (jstree.is_leaf(node))
					jstree.delete_node(node);
				else
					this.showOrHideVintPortDevices(node);
			}
		} else if (obj instanceof phidget22.Connection) {
			var jstree = $(this.treediv).jstree(true);
			var nodeid = this.mkDiv(obj);
			var node = jstree.get_node(nodeid);
			if (node === false) {
				console.log('unable to find node for:' + obj + ' (' + nodeid + ')');
				return;
			}
			jstree.delete_node(node);
		}
	}

} (window.phidget22));