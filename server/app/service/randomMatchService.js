var RandomMatchService = function(app) {
    this.app = app;
    this.first = -1;
};

module.exports = RandomMatchService;

RandomMatchService.prototype.add = function(uid,cb){
    if(this.first !== -1)
    {
        cb(this.first);
        this.first = -1;
    }
    else
    {
        cb(-1);
        this.first = uid;
    }
}
