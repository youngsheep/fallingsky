module.exports = function(app) {
  return new Handler(app);
};

var Handler = function(app) {
  this.app = app;
  this.serverId = app.get('serverId').split('-')[2];
};

// generate playerId
var id = 1;

/**
 * New client entry chat server.
 *
 * @param  {Object}   msg     request message
 * @param  {Object}   session current session object
 * @param  {Function} next    next stemp callback
 * @return {Void}
 */
Handler.prototype.entry = function(msg, session, next) {
    console.log(this.serverId);

    var self = this;
    var playerid = parseInt(this.serverId + id, 10);
    id += 1;
    session.bind(playerid);
    session.set('serverId', this.serverId);

    var data = {
        result:200,
        playerid:playerid
    };
    next(null,data);
    console.log(data);
};
