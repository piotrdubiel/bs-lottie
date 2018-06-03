;(function() {
  var node = (tag, attrs, children) => {
    var node = document.createElement(tag)
    for (var attr in attrs) {
      if (attr === 'style') {
        Object.assign(node.style, attrs[attr])
      } else {
        node.setAttribute(attr, attrs[attr])
      }
    }
    children && children.forEach(child => node.appendChild(typeof child === 'string' ? document.createTextNode(child) : child))
    return node
  }
  var named = tag => (attrs, children) => node(tag, attrs, children)
  var div = named('div')
  var span = named('span')
  var a = named('a')
  var raw = text => {
    var node = document.createElement('div')
    node.innerHTML = text
    return node
  };

  var render = (target, node) => {
    target.innerHTML = ''
    target.appendChild(node)
  };

  let loadingPromise = null
  var loadDeps = () => {
    if (loadingPromise) {
      return loadingPromise
    }
    loadingPromise = new Promise((res, rej) => {
      const src = window.relativeToRoot + '/all-deps.js'
      const script = node('script', {src});
      script.onload = () => res();
      script.onerror = e => rej(e);
      document.body.appendChild(script)
    })
    return loadingPromise
  };

  var initBlocks = () => {
    ;[].forEach.call(document.querySelectorAll('div.block-target'), el => {
      const context = el.getAttribute('data-context');
      const id = el.getAttribute('data-block-id');
      const parent = el.parentNode;

      const logs = div({class: 'block-logs'}, []);

      const addLog = (level, items) => {
        var text = ''
        if (items.length === 1 && typeof items[0] === 'string') {
          text = items[0]
        } else {
          text = JSON.stringify(items)
        }
        logs.appendChild(div({class: 'block-log level-' + level}, [text]))
      };

      let ran = false

      window.process = {env: {NODE_ENV: 'production'}}

      const runBlock = (context) => {
        if (ran) {
          return
        }
        ran = true
        loadDeps().then(() => {
          const bundle = document.querySelector('script[type=docre-bundle][data-block-id="' + id + '"]')
          console.log(id)
          if (!bundle) {
            console.error('bundle not found')
            return
          }
          const oldConsole = window.console
          window.console = {
            ...window.console,
            log: (...items) => {oldConsole.log(...items); addLog('log', items)},
            warn: (...items) => {oldConsole.warn(...items); addLog('warn', items)},
            error: (...items) => {oldConsole.error(...items); addLog('error', items)},
          }
          Object.assign(window, context)
          // ok folks we're done
          try {
            // TODO check if it's a promise or something... and maybe wait?
            eval(bundle.textContent);
          } catch (error) {
            oldConsole.error(error)
            addLog('error', [error && error.message])
          }
          window.console = oldConsole
          for (let name in context) {
            window[name] = null
          }
        })
      }

      if (context === 'canvas') {
        const play = div({class: 'block-canvas-play'}, ["▶"])
        const canvas = node('canvas', {id: 'block-canvas-' + id})
        canvas.width = 200
        canvas.height = 200
        play.onclick = () => {
          console.log('start the music!')
          play.style.display = 'none'
          runBlock({sandboxCanvas: canvas, sandboxCanvasId: canvas.id})
        }
        const canvasBlock = div({class: 'block-canvas-container'}, [
          canvas,
          play
        ]);
        parent.appendChild(canvasBlock)
      } else if (context === 'div') {
        const target = div({id: 'block-target-div-' + id})
        const container = div({class: 'block-target-container'}, [target])
        parent.appendChild(container)
        const startBlock = div({class: 'block-target-right'}, ["▶"])
        startBlock.onclick = () => {
          startBlock.style.display = 'none'
          container.classList.add('active')
          runBlock({sandboxDiv: target, sandboxDivId: target.id})
        }
        parent.appendChild(startBlock)
      } else {
        /*
        const startBlock = div({class: 'block-target-small'}, ["▶"])
        parent.appendChild(startBlock)
        startBlock.onclick = () => {
          startBlock.style.display = 'none'
          runBlock({})
        }
        */
      }

      parent.appendChild(logs)
    })
  }



var listenForTypes = () => {
  var typeViewer = document.createElement('div')
  typeViewer.className = 'type-viewer'
  document.body.appendChild(typeViewer)
  ;[].forEach.call(document.querySelectorAll('pre.code'), el => {
    el.addEventListener('mousemove', evt => {
      typeViewer.style.top = evt.pageY + 'px'
      typeViewer.style.left = evt.pageX + 'px'
    });
    el.addEventListener('mouseover', evt => {
      if (evt.target.getAttribute('data-type')) {
        evt.target.classList.add('type-hovered')
        typeViewer.textContent = evt.target.getAttribute('data-type')
        typeViewer.style.display = 'block'
      }
    })
    el.addEventListener('mouseout', evt => {
      if (evt.target.getAttribute('data-type')) {
        evt.target.classList.remove('type-hovered')
        typeViewer.style.display = 'none'
      }
    })
  })
}

var checkHash = () => {
  if (!window.shouldCheckHashes) {
    return
  }
  var id = window.location.hash.slice(1)
  if (id && !document.getElementById(id)) {
    document.getElementById("error-message").style.display = 'block'
    var parts = id.split('-')
    document.querySelector('#error-message span').textContent = parts[0]
    document.querySelector('#error-message code').textContent = parts[1]
  } else {
    document.getElementById("error-message").style.display = 'none'
  }
}
window.onload = () => {
  checkHash()
  var expander = document.querySelector('.sidebar-expander')
  expander.onclick = () => {
    var sidebar = document.querySelector('.sidebar');
    if (sidebar.classList.contains('expanded')) {
      sidebar.classList.remove('expanded')
      expander.textContent = 'Show navigation'
    } else {
      sidebar.classList.add('expanded')
      expander.textContent = 'Hide navigation'
    }
  }
  listenForTypes();
  initBlocks();
}
window.onhashchange = checkHash
})();