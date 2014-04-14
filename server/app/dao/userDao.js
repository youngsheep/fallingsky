var pomelo = require('pomelo');

var userDao = module.exports;

userDao.createPlayer = function(username,passwd,createcb){
    pomelo.app.get('dbclient').execute(function(client,execb){
        client.hsetnx("users",username ,passwd,function(err,replies){
            execb();

            if (err) {       
                console.error("error response - " + err);
                createcb(fasle);
                return;
            }

            console.log(replies);
            createcb(true);
        });
    });

};
