var pomelo = require('pomelo');
var RandomMatchService = require('../../../service/randomMatchService');

module.exports = function(app) {
    return new Handler(app);
};

var Handler = function(app) {
    this.app = app;
    if(!this.app)
        logger.error(app);

    this.matchService = new RandomMatchService(app);
};

Handler.prototype.match = function(msg, session, next) {
    this.matchService.add(session.uid,function(matchid){
        if(matchid !== -1)
        {
            var data1 = {
                result : 0,
                matchid: matchid
            };
            next(null,data1);

            var uid = {uid:matchid,sid:'connector-server-1'};
            console.log(uid);

            var data2 = {
                result : 0,
                matchid: session.uid
            };
            pomelo.app.get('channelService').pushMessageByUids('match.randomHandler.match', data2, [uid] , null);
        }
        else
        {
            var data ={
                result:100,
                matchid:0
            };
            next(null,data);
        }
    });

    console.log(msg);
};