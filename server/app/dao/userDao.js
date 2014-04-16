var pomelo = require('pomelo');

var userDao = module.exports;

userDao.createUser = function(username,passwd,createcb){
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


userDao.getUserByName = function(name,cb){
    pomelo.app.get('dbclient').execute(function(client,release){
        client.hhet("users",name ,function(err,res){
            release();
            cb(err,res);
        });
    });        
};
